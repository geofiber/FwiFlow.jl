using FwiFlow
using ADCME
using MAT
using PyPlot
using LinearAlgebra
oz = 0.0 
ox = 0.0
dz_orig = 24.0 
dx_orig = 24.0 
nz_orig = 134 
nx_orig = 384 
dz = dz_orig/1.0
dx = dx_orig/1.0
nz = Int64(round((dz_orig * nz_orig) / dz));
nx = Int64(round((dx_orig * nx_orig) / dx))
dt = 0.0025
nSteps = 2000
para_fname = "para_file.json"
survey_fname = "survey_file.json"
data_dir_name = "Data"
# source and receiver locations

ind_src_x = collect(4:8:384)
ind_src_z = 2ones(Int64, size(ind_src_x))
ind_rec_x = collect(3:381)
ind_rec_z = 2ones(Int64, size(ind_rec_x))

fwi = FWI(nz, nx, dz, dx, nSteps, dt; 
    ind_src_x = ind_src_x, ind_src_z = ind_src_z, ind_rec_x = ind_rec_x, ind_rec_z = ind_rec_z)



stf = matread("$(DATADIR)/sourceF_4p5_2_high.mat")["sourceF"][:]
cp = Float64.(reshape(reinterpret(Float32,read("$DATADIR/Model_Cp_true.bin")), (fwi.nz_pad, fwi.nx_pad)))|>Array
cs = zeros(fwi.nz_pad, fwi.nx_pad)
ρ = 2500.0 .* ones(fwi.nz_pad, fwi.nx_pad)
shot_ids = collect(1:length(ind_src_z))
sess = Session()

obs = compute_observation(sess, fwi, cp, cs, ρ, stf, shot_ids, gpu_id=0)
@assert norm(matread("test_data.mat")["obs"]-obs)≈0.0
@info "Forward test passed!"

close("all")
imshow(obs[10,:,:], vmax=2000, vmin=-2000, extent=[0, fwi.nx*fwi.dx, fwi.dt*(fwi.nSteps-1), 0])
xlabel("Receiver Location (m)")
ylabel("Time (s)")
colorbar()
axis("normal")
set_cmap("gray")
savefig("Utils.png")

cs_init = zeros(fwi.nz_pad, fwi.nx_pad)
ρ_init = 2500.0 .* ones(fwi.nz_pad, fwi.nx_pad)
cp_init = Float64.(reshape(reinterpret(Float32,read("$DATADIR/Model_Cp_init_1D.bin")), (fwi.nz_pad, fwi.nx_pad)))|>Array

# make variables
cs_inv = Variable(cs_init)
ρ_inv = Variable(ρ_init)
cp_inv = Variable(cp_init)

# allocate GPUs
loss = constant(0.0)
nGpus = length(use_gpu())
shot_id_points = Int64.(trunc.(collect(LinRange(1, length(ind_src_z), nGpus+1))))

@info "$nGpus GPU(s) is(are) available."
loss = constant(0.0)
for i = 1:nGpus
    global loss
    shot_ids = collect(shot_id_points[i]:shot_id_points[i+1])
    loss += compute_misfit(fwi, cp_inv, cs_inv, ρ_inv, 
            stf , shot_ids; gpu_id = i-1,
            is_masked = false, cp_ref = cp_init, cs_ref =  cs_init, ρ_ref = ρ_init)
end


g_cs = gradients(loss, cs_inv)
g_ρ = gradients(loss, ρ_inv)
g_cp = gradients(loss, cp_inv)

matfile = matread("test_data.mat")
gcs, gρ, gcp = matfile["cs"], matfile["rho"], matfile["cp"]
sess = Session(); init(sess)
err = run(sess, loss)
@info "initial error = ", err
a, b, c = run(sess, [g_cs, g_ρ, g_cp])
if maximum(abs.(a-gcs))<1e-3 && 
    maximum(abs.(b-gρ))<1e-3 && 
    maximum(abs.(c-gcp))<1e-3 
    
    @info "gradient is correct"
else 
    @info "gradient is incorrect"
end
BFGS!(sess, loss)
