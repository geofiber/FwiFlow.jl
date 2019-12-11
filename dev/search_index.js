var documenterSearchIndex = {"docs":
[{"location":"api/#API-Reference-1","page":"API Reference","title":"API Reference","text":"","category":"section"},{"location":"api/#","page":"API Reference","title":"API Reference","text":"(Image: )","category":"page"},{"location":"api/#","page":"API Reference","title":"API Reference","text":"poisson_op\nlaplacian_op\nfwi_obs_op\nfwi_op\nsat_op\nupwlap_op","category":"page"},{"location":"api/#FwiFlow.poisson_op","page":"API Reference","title":"FwiFlow.poisson_op","text":"poisson_op(c::Union{PyObject, Float64}, g::Union{PyObject, Float64}, \n    h::Union{PyObject, Float64}, ρ::Union{PyObject, Float64}, index::Union{Integer, PyObject}=0)\n\nSolves the Poisson equation (mathbfx=zquad x^T)\n\nbeginaligned\n-nablacdotleft(c(mathbfx) nabla left(u(mathbfx) -rho  beginbmatrixz  0endbmatrix   right)right) =  g(mathbfx)  mathbfxin Omega\nfracpartial u(x)partial n =  0  mathbfxin Omega\nendaligned\n\nHere Omega=0n_zhtimes 0 n_xh. The equation is solved using finite difference method, where the step size in each direction is h. Mathematically, the solution to the PDE is determined up to a constant. Numerically, we discretize the equation with the scheme\n\n(A+E_11)mathbfu = mathbff\n\nwhere A is the finite difference coefficient matrix,\n\n(E_11)_ij = left beginmatrix1  i=j=1  0  mbox otherwise endmatrixright\n\nindex : Int32, when index=1, SparseLU is used to solve the linear system; otherwise the function invokes algebraic multigrid method from amgcl. \n\n\n\n\n\n","category":"function"},{"location":"api/#FwiFlow.laplacian_op","page":"API Reference","title":"FwiFlow.laplacian_op","text":"laplacian_op(coef::Union{PyObject, Array{Float64}}, f::Union{PyObject, Array{Float64}}, \n        h::Union{PyObject, Float64}, ρ::Union{PyObject, Float64})\n\nComputes the Laplacian of function f(mathbfx); here (mathbfx=zquad x^T)\n\n-nablacdotleft(c(mathbfx) nabla left(u(mathbfx) -rho beginbmatrixz  0endbmatrix  right)right)\n\n\n\n\n\n","category":"function"},{"location":"api/#FwiFlow.fwi_obs_op","page":"API Reference","title":"FwiFlow.fwi_obs_op","text":"fwi_obs_op(cp::Union{PyObject, Array{Float64}},cs::Union{PyObject, Array{Float64}},\n    den::Union{PyObject, Array{Float64}},stf::Union{PyObject, Array{Float64}},\n    gpu_id::Union{PyObject, Integer},shot_ids::Union{PyObject, Array{T}},para_fname::String) where T<:Integer\n\nGenerates the observation data and store them as files which will be used by fwi_op For the meaning of parameters, see fwi_op.\n\n\n\n\n\n","category":"function"},{"location":"api/#FwiFlow.fwi_op","page":"API Reference","title":"FwiFlow.fwi_op","text":"fwi_op(cp::Union{PyObject, Array{Float64}},cs::Union{PyObject, Array{Float64}},\nden::Union{PyObject, Array{Float64}},stf::Union{PyObject, Array{Float64}},\ngpu_id::Union{PyObject, Integer},shot_ids::Union{PyObject, Array{T}},para_fname::String) where T<:Integer\n\nComputes the FWI loss function. \n\ncp : P-wave velocity\ncs : S-wave velocity\nden : Density \nstf : Source time functions  \ngpu_id : The ID of GPU to run this FWI operator\nshot_ids : The source function IDs (determining the location of sources)\npara_fname : Parameter file location\n\n\n\n\n\n","category":"function"},{"location":"api/#FwiFlow.sat_op","page":"API Reference","title":"FwiFlow.sat_op","text":"sat_op(s0::Union{PyObject, Array{Float64}},pt::Union{PyObject, Array{Float64}},\npermi::Union{PyObject, Array{Float64}},poro::Union{PyObject, Array{Float64}},\nqw::Union{PyObject, Array{Float64}},qo::Union{PyObject, Array{Float64}},\nmuw::Union{PyObject, Float64},muo::Union{PyObject, Float64},\nsref::Union{PyObject, Array{Float64}},dt::Union{PyObject, Float64},h::Union{PyObject, Float64})\n\nSolves the following discretized equation \n\nphi (S_2^n + 1 - S_2^n) - nabla  cdot left( m_2(S_2^n + 1)Knabla Psi _2^n right) Delta t= left(q_2^n + q_1^n fracm_2(S^n+1_2)m_1(S^n+1_2)right) Delta t\n\nwhere\n\nm_2(s) = fracs^2mu_wqquad m_1(s) = frac(1-s)^2mu_o\n\nThis is a nonlinear equation and is solved with the Newton-Raphson method. \n\ns0 : n_ztimes n_x, saturation of fluid, i.e., S_2^n\npt : n_ztimes n_x, potential of fluid, i.e., Psi_2^n\npermi : n_ztimes n_x, permeability, i.e., K \nporo : n_ztimes n_x, porosity, i.e., phi\nqw : n_ztimes n_x, injection or production rate of ﬂuid 1, q_2^n\nqo : n_ztimes n_x, injection or production rate of ﬂuid 2, q_1^n\nmuw : viscosity of fluid 1, i.e., mu_w\nmuo : viscosity of fluid 2, i.e., mu_o\nsref : n_ztimes n_x, initial guess for S_2^n+1\ndt : Time step size  \nh : Spatial step size\n\n\n\n\n\n","category":"function"},{"location":"api/#FwiFlow.upwlap_op","page":"API Reference","title":"FwiFlow.upwlap_op","text":"upwlap_op(perm::Union{PyObject, Array{Float64}},\nmobi::Union{PyObject, Array{Float64}},\nfunc::Union{PyObject, Array{Float64}},\nh::Union{PyObject, Float64},\nrhograv::Union{PyObject, Float64})\n\nComputes the Laplacian of function f(mathbfx); here mathbfx=zquad x^T.\n\nnablacdotleft(m(mathbfx)K(mathbfx) nabla left(f(mathbfx) -rho beginbmatrixz  0endbmatrix  right)right)\n\nThe permeability on the computational grid is computed with Harmonic mean;  the mobility is computed with upwind scheme. \n\nperm : n_ztimes n_x, permeability of fluid, i.e., K\nmobi : n_ztimes n_x, mobility of fluid, i.e., m\nfunc : n_ztimes n_x, potential of fluid, i.e., f\nh : Float64, spatial step size \nrhograv : Float64, i.e., rho\n\n\n\n\n\n","category":"function"},{"location":"api/#","page":"API Reference","title":"API Reference","text":"Modules = [FwiFlow]\nPages   = [\"utils.jl\"]","category":"page"},{"location":"api/#FwiFlow.paraGen-NTuple{12,Any}","page":"API Reference","title":"FwiFlow.paraGen","text":"Generates a parameter file consumed by fwi_op and fwi_op_ops\n\nnSteps : Number of time steps in the simulation \ndt : Time step \nf0 : Source frequency \nnPoints_pml : Number of points in PML boundary condition \nnPad : Padding width \nif_win : \nfilter : Whether apply filters \nif_src_update : \nsurvey_fname : The name of the survey file \ndata_dir_name : Locations for storing observation data (generated by fwi_op_ops, in the form of .bin)\nscratch_dir_name : Temporary data location \n\n\n\n\n\n","category":"method"},{"location":"api/#FwiFlow.surveyGen-Tuple{Array{Integer,N} where N,Any,Any,Any,Any}","page":"API Reference","title":"FwiFlow.surveyGen","text":"Generates the survey parameter file. \n\nz_src : z coordinates of sources\nx_src : x coordinates of sources\nz_rec : z coordinates of receivers\nx_rec : x coordinates of receiverss\nsurvey_fname : The name of the survey file \nWindows : \nWeights : \n\n\n\n\n\n","category":"method"},{"location":"api/#FwiFlow.cs_bounds_cloud-Tuple{Any,Any}","page":"API Reference","title":"FwiFlow.cs_bounds_cloud","text":"get vs upper and lower bounds from log point cloud \n\n1st row of Bounds: vp ref line\n2nd row of Bounds: vs high ref line\n3rd row of Bounds: vs low ref line\n\n\n\n\n\n","category":"method"},{"location":"api/#FwiFlow.klauderWave-NTuple{6,Any}","page":"API Reference","title":"FwiFlow.klauderWave","text":"Generates Klauder wavelet\n\nDongzhuo Li @ Stanford August, 2019\n\n\n\n\n\n","category":"method"},{"location":"api/#FwiFlow.sourceGene-Tuple{Float64,Integer,Float64}","page":"API Reference","title":"FwiFlow.sourceGene","text":"sourceGene(f::Float64, nStep::Integer, delta_t::Float64)\n\nGenerates Ricker wavelets.\n\n\n\n\n\n","category":"method"},{"location":"troubleshooting/#Trouble-Shooting-1","page":"Trouble Shooting","title":"Trouble Shooting","text":"","category":"section"},{"location":"troubleshooting/#AMG-1","page":"Trouble Shooting","title":"AMG","text":"","category":"section"},{"location":"README/#FwiFlow-1","page":"FwiFlow","title":"FwiFlow","text":"","category":"section"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"<img src=\"../assets/diagram.png\" style=\"zoom:67%;\" />","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"This project consider the coupling of the wave equation and a two-phase incompressible immiscible flow equation, mainly for CO2 injection or water injection monitoring","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"utt = m(x) uxx + f(x,t)","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"m_t = grad(a(x)grad(m)) + b(x)*grad(m)","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"The time scale T2 for the second equation is much larger than that of the first one T1","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"T2 >> T1","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"a(x), b(x) are unknown functions and will be calibrated using observation data di(x), which depends on ui for each observation time i","category":"page"},{"location":"README/#Instruction-1","page":"FwiFlow","title":"Instruction","text":"","category":"section"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Compile AdvectionDiffusion","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"cd Ops/AdvectionDiffusion/\nmkdir build\ncd build\ncmake ..\nmake -j","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Test AdvectionDiffusion and Generate Data (required)","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"julia> include(\"cdtest.jl\")\njulia> include(\"gradtest.jl\")","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Compile CUFA","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"cd Ops/FWI/CUFD/Src\nmake -j","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Compile Wrapper","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"cd Ops/FWI/ops/build\ncmake ..\nmake -j","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Generate data","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"julia> include(\"generate_m.jl\")\npython main_calc_obs_data.py\npython fwitest.py","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Test Wrapper","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"cd src","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"julia> include(\"fwi_gradient_check.jl\")\njulia> include(\"coupled_gradient_check\")","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"Run experiments","category":"page"},{"location":"README/#","page":"FwiFlow","title":"FwiFlow","text":"julia> include(\"learn_m.jl\")","category":"page"},{"location":"#Getting-Started-1","page":"Getting Started","title":"Getting Started","text":"","category":"section"},{"location":"#Installation-1","page":"Getting Started","title":"Installation","text":"","category":"section"},{"location":"#General-Problem-1","page":"Getting Started","title":"General Problem","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"This framework uses waveform data to invert for intrinsic parameters (e.g., permeability and porosity) in subsurface problems, with coupled flow physics, rock physics, and wave physics models.","category":"page"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"(Image: )","category":"page"},{"location":"#Physical-Models-1","page":"Getting Started","title":"Physical Models","text":"","category":"section"},{"location":"#Flow-Physics-1","page":"Getting Started","title":"Flow Physics","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"The flow physics component maps from intrinsic properties such as permeability to flow properties, such as fluid saturation. We use a model of two-phase flow in porous media as an example. The governing equations are convervation of mass, Darcy's law, and other relationships.","category":"page"},{"location":"#Rock-Physics-1","page":"Getting Started","title":"Rock Physics","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"The rock physics model describes the relationship between fluid properties and rock elastic properties. As one fluid phase displaces the other, the bulk modulus and density of rocks vary. ","category":"page"},{"location":"#Wave-Physics-1","page":"Getting Started","title":"Wave Physics","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"The elastic wave equation maps from elastic properties to wavefields, such as particle velocity and stress, which can be recorded by receiver arrays as seismic waveform data.","category":"page"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"The elastic wave equation maps from elastic properties to wavefields, such as particle velocity and stress, which can be recorded by receiver arrays as seismic waveform data.","category":"page"},{"location":"#Intelligent-Automatic-Differentiation-1","page":"Getting Started","title":"Intelligent Automatic Differentiation","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"The Intelligent Automatic Differentiation method provides three levels of user control with (1) built-in differentiable operators from modern deep-learning infrastructures (TensorFlow), and customized operators that can either (2) encapsulate analytic adjoint gradient computation or (3) handle the forward simulation and compute the corresponding gradient for a single time step. This intelligent strategy strikes a good balance between computational efficiency and programming efficiency and would serve as a paradigm for a wide range of PDE-constrained geophysical inverse problems.","category":"page"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"###\tThe Adjoint Method & Automatic Differentation","category":"page"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"(Image: )","category":"page"},{"location":"#The-Adjoint-Method-and-Automatic-Differentation-1","page":"Getting Started","title":"The Adjoint Method & Automatic Differentation","text":"","category":"section"},{"location":"#Customized-Operators-1","page":"Getting Started","title":"Customized Operators","text":"","category":"section"},{"location":"#","page":"Getting Started","title":"Getting Started","text":"###\tCustomized Operators","category":"page"},{"location":"tutorial/#Tutorial-1","page":"Tutorial","title":"Tutorial","text":"","category":"section"},{"location":"tutorial/#FWI-1","page":"Tutorial","title":"FWI","text":"","category":"section"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We consider a standard FWI problem. First of all, we load necessary packages","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"using FwiFlow\nusing PyCall\nusing LinearAlgebra\nusing PyPlot\nusing Random\nnp = pyimport(\"numpy\")","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We specify several parameters","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"nz = 134\nnx = 384\ndz = 24. # meters\ndx = 24.\nnSteps = 2001\ndt = 0.0025\nf0 = 4.5\nfilter_para = [0, 0.1, 100.0, 200.0]\nisAc = true\nnPml = 32\nnPad = 32 - mod((nz+2*nPml), 32)\nnz_pad = nz + 2*nPml + nPad\nnx_pad = nx + 2*nPml","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We will use the reflection type of problem: sources on one side and receivers on the other side. ","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"x_src = collect(4:8:384)\nz_src = 2ones(Int64, size(x_src))\nx_rec = collect(3:381)\nz_rec = 2ones(Int64, size(x_rec))","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"Now we generate the parameter files ","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"para_fname = \"./para_file.json\"\nsurvey_fname = \"./survey_file.json\"\ndata_dir_name = \"./Data\"\nparaGen(nz_pad, nx_pad, dz, dx, nSteps, dt, f0, nPml, nPad, filter_para, isAc, para_fname, survey_fname, data_dir_name)\nsurveyGen(z_src, x_src, z_rec, x_rec, survey_fname)","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We load a true model from the file Model_Cp_true.bin and specify all necessary parameters to run on 2 GPUs","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"tf_cp = constant(reshape(reinterpret(Float32,read(\"Mar_models/Model_Cp_true.bin\")),(nz_pad, nx_pad)), dtype=Float64)\ncs = zeros(nz_pad, nx_pad)\nden = 1000.0 .* ones(nz_pad, nx_pad)\ncp_pad_value = 3000.0\n\ntf_cs = constant(cs)\ntf_den = constant(den)\n\nsrc = Matrix{Float64}(undef, 1, 2001)\nsrc[1,:] = Float64.(reinterpret(Float32, read(\"../Ops/FWI/Src/params/Mar_source_2001.bin\")))\ntf_stf = constant(repeat(src, outer=length(z_src)))\n\ntf_gpu_id0 = constant(0, dtype=Int32)\ntf_gpu_id1 = constant(1, dtype=Int32)\nnGpus = 2\ntf_gpu_id_array = constant(collect(0:nGpus-1), dtype=Int32)\ntf_shot_ids0 = constant(collect(Int32, 0:length(x_src)-1), dtype=Int32)\nshot_id_points = Int32.(trunc.(collect(LinRange(0, length(z_src)-1, nGpus+1))))","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"Now it's ready to generate the observation data. ","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"res = fwi_obs_op(tf_cp, tf_cs, tf_den, tf_stf, tf_gpu_id0, tf_shot_ids0, para_fname)\nsess = Session(); init(sess);\nrun(sess, res)","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We can see some files are generated in the folder XXXX. We now consider inversion: cp is not known. The idea is to make cp as an independent variable to be updated; this can be done by specifying cp with Variable","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"cp_init = reshape(reinterpret(Float32,read(\"Mar_models/Model_Cp_init_1D.bin\")),(nz_pad, nx_pad))\ntf_cp_inv = Variable(cp_init, dtype=Float64)\n\nMask = ones(nz_pad, nx_pad)\nMask[nPml+1:nPml+10,:] .= 0.0\ntf_cp_inv_msk = tf_cp_inv .* constant(Mask) + constant(cp_init[1,1] .* (1. .- Mask))","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"We have used the mask trick to make the computation numerically stable. ","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"Now we can form the loss function with fwi_op and optimizes it with ADCME","category":"page"},{"location":"tutorial/#","page":"Tutorial","title":"Tutorial","text":"loss = fwi_op(tf_cp_inv_msk, tf_cs, tf_den, tf_stf, tf_gpu_id_array[1], tf_shot_ids0, para_fname)\nsess = Session(); init(sess)\nBFGS!(sess, loss)","category":"page"}]
}
