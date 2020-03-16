#include "tensorflow/core/framework/op_kernel.h"
#include "tensorflow/core/framework/tensor_shape.h"
#include "tensorflow/core/platform/default/logging.h"
#include "tensorflow/core/framework/shape_inference.h"
#include<cmath>


#ifdef USE_GPU
#include "tensorflow/core/util/gpu_kernel_helper.h"
namespace tensorflow{
  typedef Eigen::GpuDevice GPUDevice;
  void forwardGPU(const GPUDevice &d);
  void backwardGPU(const GPUDevice &d);
}
#endif
using namespace tensorflow;
#include "Saturation.h"


REGISTER_OP("Saturation")

.Input("s0 : double")
.Input("dporodt : double")
.Input("pt : double")
.Input("perm : double")
.Input("poro : double")
.Input("qw : double")
.Input("qo : double")
.Input("muw : double")
.Input("muo : double")
.Input("sref : double")
.Input("dt : double")
.Input("h : double")
.Output("sat : double")
.SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
    
        shape_inference::ShapeHandle s0_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(0), 2, &s0_shape));
        shape_inference::ShapeHandle dporodt_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(1), 2, &dporodt_shape));
        shape_inference::ShapeHandle pt_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(2), 2, &pt_shape));
        shape_inference::ShapeHandle perm_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(3), 2, &perm_shape));
        shape_inference::ShapeHandle poro_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(4), 2, &poro_shape));
        shape_inference::ShapeHandle qw_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(5), 2, &qw_shape));
        shape_inference::ShapeHandle qo_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(6), 2, &qo_shape));
        shape_inference::ShapeHandle muw_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(7), 0, &muw_shape));
        shape_inference::ShapeHandle muo_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(8), 0, &muo_shape));
        shape_inference::ShapeHandle sref_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(9), 2, &sref_shape));
        shape_inference::ShapeHandle dt_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(10), 0, &dt_shape));
        shape_inference::ShapeHandle h_shape;
        TF_RETURN_IF_ERROR(c->WithRank(c->input(11), 0, &h_shape));

        c->set_output(0, c->Matrix(-1,-1));
    return Status::OK();
  });

REGISTER_OP("SaturationGrad")

.Input("grad_sat : double")
.Input("sat : double")
.Input("s0 : double")
.Input("dporodt : double")
.Input("pt : double")
.Input("perm : double")
.Input("poro : double")
.Input("qw : double")
.Input("qo : double")
.Input("muw : double")
.Input("muo : double")
.Input("sref : double")
.Input("dt : double")
.Input("h : double")
.Output("grad_s0 : double")
.Output("grad_dporodt : double")
.Output("grad_pt : double")
.Output("grad_perm : double")
.Output("grad_poro : double")
.Output("grad_qw : double")
.Output("grad_qo : double")
.Output("grad_muw : double")
.Output("grad_muo : double")
.Output("grad_sref : double")
.Output("grad_dt : double")
.Output("grad_h : double");


class SaturationOp : public OpKernel {
private:
  
public:
  explicit SaturationOp(OpKernelConstruction* context) : OpKernel(context) {

  }

  void Compute(OpKernelContext* context) override {    
    DCHECK_EQ(12, context->num_inputs());
    
    
    const Tensor& s0 = context->input(0);
    const Tensor& dporodt = context->input(1);
    const Tensor& pt = context->input(2);
    const Tensor& perm = context->input(3);
    const Tensor& poro = context->input(4);
    const Tensor& qw = context->input(5);
    const Tensor& qo = context->input(6);
    const Tensor& muw = context->input(7);
    const Tensor& muo = context->input(8);
    const Tensor& sref = context->input(9);
    const Tensor& dt = context->input(10);
    const Tensor& h = context->input(11);
    
    
    const TensorShape& s0_shape = s0.shape();
    const TensorShape& dporodt_shape = dporodt.shape();
    const TensorShape& pt_shape = pt.shape();
    const TensorShape& perm_shape = perm.shape();
    const TensorShape& poro_shape = poro.shape();
    const TensorShape& qw_shape = qw.shape();
    const TensorShape& qo_shape = qo.shape();
    const TensorShape& muw_shape = muw.shape();
    const TensorShape& muo_shape = muo.shape();
    const TensorShape& sref_shape = sref.shape();
    const TensorShape& dt_shape = dt.shape();
    const TensorShape& h_shape = h.shape();
    
    
    DCHECK_EQ(s0_shape.dims(), 2);
    DCHECK_EQ(dporodt_shape.dims(), 2);
    DCHECK_EQ(pt_shape.dims(), 2);
    DCHECK_EQ(perm_shape.dims(), 2);
    DCHECK_EQ(poro_shape.dims(), 2);
    DCHECK_EQ(qw_shape.dims(), 2);
    DCHECK_EQ(qo_shape.dims(), 2);
    DCHECK_EQ(muw_shape.dims(), 0);
    DCHECK_EQ(muo_shape.dims(), 0);
    DCHECK_EQ(sref_shape.dims(), 2);
    DCHECK_EQ(dt_shape.dims(), 0);
    DCHECK_EQ(h_shape.dims(), 0);

    // extra check
        
    // create output shape
    int nz = s0_shape.dim_size(0), nx = s0_shape.dim_size(1);
    TensorShape sat_shape({nz, nx});
            
    // create output tensor
    
    Tensor* sat = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, sat_shape, &sat));
    
    // get the corresponding Eigen tensors for data access
    
    auto s0_tensor = s0.flat<double>().data();
    auto dporodt_tensor = dporodt.flat<double>().data();
    auto pt_tensor = pt.flat<double>().data();
    auto perm_tensor = perm.flat<double>().data();
    auto poro_tensor = poro.flat<double>().data();
    auto qw_tensor = qw.flat<double>().data();
    auto qo_tensor = qo.flat<double>().data();
    auto muw_tensor = muw.flat<double>().data();
    auto muo_tensor = muo.flat<double>().data();
    auto sref_tensor = sref.flat<double>().data();
    auto dt_tensor = dt.flat<double>().data();
    auto h_tensor = h.flat<double>().data();
    auto sat_tensor = sat->flat<double>().data();   

    // implement your forward function here 

    // TODO:
    mu_w = *muw_tensor;
    mu_o = *muo_tensor;
    forward(sat_tensor, dporodt_tensor, s0_tensor, pt_tensor, perm_tensor, poro_tensor,
            qw_tensor, qo_tensor, sref_tensor, *dt_tensor, *h_tensor, nz, nx);

  }
};
REGISTER_KERNEL_BUILDER(Name("Saturation").Device(DEVICE_CPU), SaturationOp);



class SaturationGradOp : public OpKernel {
private:
  
public:
  explicit SaturationGradOp(OpKernelConstruction* context) : OpKernel(context) {
    
  }
  
  void Compute(OpKernelContext* context) override {
    
    
    const Tensor& grad_sat = context->input(0);
    const Tensor& sat = context->input(1);
    const Tensor& s0 = context->input(2);
    const Tensor& dporodt = context->input(3);
    const Tensor& pt = context->input(4);
    const Tensor& perm = context->input(5);
    const Tensor& poro = context->input(6);
    const Tensor& qw = context->input(7);
    const Tensor& qo = context->input(8);
    const Tensor& muw = context->input(9);
    const Tensor& muo = context->input(10);
    const Tensor& sref = context->input(11);
    const Tensor& dt = context->input(12);
    const Tensor& h = context->input(13);
    
    
    const TensorShape& grad_sat_shape = grad_sat.shape();
    const TensorShape& sat_shape = sat.shape();
    const TensorShape& s0_shape = s0.shape();
    const TensorShape& dporodt_shape = dporodt.shape();
    const TensorShape& pt_shape = pt.shape();
    const TensorShape& perm_shape = perm.shape();
    const TensorShape& poro_shape = poro.shape();
    const TensorShape& qw_shape = qw.shape();
    const TensorShape& qo_shape = qo.shape();
    const TensorShape& muw_shape = muw.shape();
    const TensorShape& muo_shape = muo.shape();
    const TensorShape& sref_shape = sref.shape();
    const TensorShape& dt_shape = dt.shape();
    const TensorShape& h_shape = h.shape();
    
    
    DCHECK_EQ(grad_sat_shape.dims(), 2);
    DCHECK_EQ(sat_shape.dims(), 2);
    DCHECK_EQ(s0_shape.dims(), 2);
    DCHECK_EQ(dporodt_shape.dims(), 2);
    DCHECK_EQ(pt_shape.dims(), 2);
    DCHECK_EQ(perm_shape.dims(), 2);
    DCHECK_EQ(poro_shape.dims(), 2);
    DCHECK_EQ(qw_shape.dims(), 2);
    DCHECK_EQ(qo_shape.dims(), 2);
    DCHECK_EQ(muw_shape.dims(), 0);
    DCHECK_EQ(muo_shape.dims(), 0);
    DCHECK_EQ(sref_shape.dims(), 2);
    DCHECK_EQ(dt_shape.dims(), 0);
    DCHECK_EQ(h_shape.dims(), 0);

    // extra check
    // int m = Example.dim_size(0);
        
    // create output shape
    
    TensorShape grad_s0_shape(s0_shape);
    TensorShape grad_dporodt_shape(dporodt_shape);
    TensorShape grad_pt_shape(pt_shape);
    TensorShape grad_perm_shape(perm_shape);
    TensorShape grad_poro_shape(poro_shape);
    TensorShape grad_qw_shape(qw_shape);
    TensorShape grad_qo_shape(qo_shape);
    TensorShape grad_muw_shape(muw_shape);
    TensorShape grad_muo_shape(muo_shape);
    TensorShape grad_sref_shape(sref_shape);
    TensorShape grad_dt_shape(dt_shape);
    TensorShape grad_h_shape(h_shape);
            
    // create output tensor
    
    Tensor* grad_s0 = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, grad_s0_shape, &grad_s0));
    Tensor* grad_dporodt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(1, grad_dporodt_shape, &grad_dporodt));
    Tensor* grad_pt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(2, grad_pt_shape, &grad_pt));
    Tensor* grad_perm = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(3, grad_perm_shape, &grad_perm));
    Tensor* grad_poro = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(4, grad_poro_shape, &grad_poro));
    Tensor* grad_qw = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(5, grad_qw_shape, &grad_qw));
    Tensor* grad_qo = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(6, grad_qo_shape, &grad_qo));
    Tensor* grad_muw = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(7, grad_muw_shape, &grad_muw));
    Tensor* grad_muo = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(8, grad_muo_shape, &grad_muo));
    Tensor* grad_sref = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(9, grad_sref_shape, &grad_sref));
    Tensor* grad_dt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(10, grad_dt_shape, &grad_dt));
    Tensor* grad_h = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(11, grad_h_shape, &grad_h));
    
    // get the corresponding Eigen tensors for data access
    
    auto s0_tensor = s0.flat<double>().data();
    auto dporodt_tensor = dporodt.flat<double>().data();
    auto pt_tensor = pt.flat<double>().data();
    auto perm_tensor = perm.flat<double>().data();
    auto poro_tensor = poro.flat<double>().data();
    auto qw_tensor = qw.flat<double>().data();
    auto qo_tensor = qo.flat<double>().data();
    auto muw_tensor = muw.flat<double>().data();
    auto muo_tensor = muo.flat<double>().data();
    auto sref_tensor = sref.flat<double>().data();
    auto dt_tensor = dt.flat<double>().data();
    auto h_tensor = h.flat<double>().data();
    auto grad_sat_tensor = grad_sat.flat<double>().data();
    auto sat_tensor = sat.flat<double>().data();
    auto grad_s0_tensor = grad_s0->flat<double>().data();
    auto grad_dporodt_tensor = grad_dporodt->flat<double>().data();
    auto grad_pt_tensor = grad_pt->flat<double>().data();
    auto grad_perm_tensor = grad_perm->flat<double>().data();
    auto grad_poro_tensor = grad_poro->flat<double>().data();
    // auto grad_qw_tensor = grad_qw->flat<double>().data();
    // auto grad_qo_tensor = grad_qo->flat<double>().data();
    // auto grad_muw_tensor = grad_muw->flat<double>().data();
    // auto grad_muo_tensor = grad_muo->flat<double>().data();
    auto grad_sref_tensor = grad_sref->flat<double>().data();
    // auto grad_dt_tensor = grad_dt->flat<double>().data();
    // auto grad_h_tensor = grad_h->flat<double>().data();   

    // implement your backward function here 

    // TODO:
    int nz = s0_shape.dim_size(0), nx = s0_shape.dim_size(1);
    mu_w = *muw_tensor;
    mu_o = *muo_tensor;
    backward(grad_sat_tensor, sat_tensor, s0_tensor, dporodt_tensor, pt_tensor, perm_tensor,
             poro_tensor, qw_tensor, qo_tensor, *dt_tensor, *h_tensor, nz, nx,
             grad_s0_tensor, grad_dporodt_tensor, grad_pt_tensor, grad_perm_tensor,
             grad_poro_tensor);
    // set other not-used gradident to zeros
    for (int i = 0; i < nz * nx; i++) {
    //   grad_qw_tensor[i] = 0.0;
    //   grad_qo_tensor[i] = 0.0;
      grad_sref_tensor[i] = 0.0;
    }
    // *grad_muw_tensor = 0.0;
    // *grad_muo_tensor = 0.0;
    // *grad_dt_tensor = 0.0;
    // *grad_h_tensor = 0.0;
  
    
  }
};
REGISTER_KERNEL_BUILDER(Name("SaturationGrad").Device(DEVICE_CPU), SaturationGradOp);


/***************************************************************************************
**********************            GPU Operator            ******************************
***************************************************************************************/


#ifdef USE_GPU
class SaturationOpGPU : public OpKernel {
private:
  
public:
  explicit SaturationOpGPU(OpKernelConstruction* context) : OpKernel(context) {

  }

  void Compute(OpKernelContext* context) override {    
    DCHECK_EQ(12, context->num_inputs());
    
    
    const Tensor& s0 = context->input(0);
    const Tensor& dporodt = context->input(1);
    const Tensor& pt = context->input(2);
    const Tensor& perm = context->input(3);
    const Tensor& poro = context->input(4);
    const Tensor& qw = context->input(5);
    const Tensor& qo = context->input(6);
    const Tensor& muw = context->input(7);
    const Tensor& muo = context->input(8);
    const Tensor& sref = context->input(9);
    const Tensor& dt = context->input(10);
    const Tensor& h = context->input(11);
    
    
    const TensorShape& s0_shape = s0.shape();
    const TensorShape& dporodt_shape = dporodt.shape();
    const TensorShape& pt_shape = pt.shape();
    const TensorShape& perm_shape = perm.shape();
    const TensorShape& poro_shape = poro.shape();
    const TensorShape& qw_shape = qw.shape();
    const TensorShape& qo_shape = qo.shape();
    const TensorShape& muw_shape = muw.shape();
    const TensorShape& muo_shape = muo.shape();
    const TensorShape& sref_shape = sref.shape();
    const TensorShape& dt_shape = dt.shape();
    const TensorShape& h_shape = h.shape();
    
    
    DCHECK_EQ(s0_shape.dims(), 2);
    DCHECK_EQ(dporodt_shape.dims(), 2);
    DCHECK_EQ(pt_shape.dims(), 2);
    DCHECK_EQ(perm_shape.dims(), 2);
    DCHECK_EQ(poro_shape.dims(), 2);
    DCHECK_EQ(qw_shape.dims(), 2);
    DCHECK_EQ(qo_shape.dims(), 2);
    DCHECK_EQ(muw_shape.dims(), 2);
    DCHECK_EQ(muo_shape.dims(), 2);
    DCHECK_EQ(sref_shape.dims(), 2);
    DCHECK_EQ(dt_shape.dims(), 0);
    DCHECK_EQ(h_shape.dims(), 0);

    // extra check
        
    // create output shape
    
    TensorShape sat_shape({-1,-1});
            
    // create output tensor
    
    Tensor* sat = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, sat_shape, &sat));
    
    // get the corresponding Eigen tensors for data access
    
    auto s0_tensor = s0.flat<double>().data();
    auto dporodt_tensor = dporodt.flat<double>().data();
    auto pt_tensor = pt.flat<double>().data();
    auto perm_tensor = perm.flat<double>().data();
    auto poro_tensor = poro.flat<double>().data();
    auto qw_tensor = qw.flat<double>().data();
    auto qo_tensor = qo.flat<double>().data();
    auto muw_tensor = muw.flat<double>().data();
    auto muo_tensor = muo.flat<double>().data();
    auto sref_tensor = sref.flat<double>().data();
    auto dt_tensor = dt.flat<double>().data();
    auto h_tensor = h.flat<double>().data();
    auto sat_tensor = sat->flat<double>().data();   

    // implement your forward function here 

    // TODO:

  }
};
REGISTER_KERNEL_BUILDER(Name("Saturation").Device(DEVICE_GPU), SaturationOpGPU);

class SaturationGradOpGPU : public OpKernel {
private:
  
public:
  explicit SaturationGradOpGPU(OpKernelConstruction* context) : OpKernel(context) {
    
  }
  
  void Compute(OpKernelContext* context) override {
    
    
    const Tensor& grad_sat = context->input(0);
    const Tensor& sat = context->input(1);
    const Tensor& s0 = context->input(2);
    const Tensor& dporodt = context->input(3);
    const Tensor& pt = context->input(4);
    const Tensor& perm = context->input(5);
    const Tensor& poro = context->input(6);
    const Tensor& qw = context->input(7);
    const Tensor& qo = context->input(8);
    const Tensor& muw = context->input(9);
    const Tensor& muo = context->input(10);
    const Tensor& sref = context->input(11);
    const Tensor& dt = context->input(12);
    const Tensor& h = context->input(13);
    
    
    const TensorShape& grad_sat_shape = grad_sat.shape();
    const TensorShape& sat_shape = sat.shape();
    const TensorShape& s0_shape = s0.shape();
    const TensorShape& dporodt_shape = dporodt.shape();
    const TensorShape& pt_shape = pt.shape();
    const TensorShape& perm_shape = perm.shape();
    const TensorShape& poro_shape = poro.shape();
    const TensorShape& qw_shape = qw.shape();
    const TensorShape& qo_shape = qo.shape();
    const TensorShape& muw_shape = muw.shape();
    const TensorShape& muo_shape = muo.shape();
    const TensorShape& sref_shape = sref.shape();
    const TensorShape& dt_shape = dt.shape();
    const TensorShape& h_shape = h.shape();
    
    
    DCHECK_EQ(grad_sat_shape.dims(), 2);
    DCHECK_EQ(sat_shape.dims(), 2);
    DCHECK_EQ(s0_shape.dims(), 2);
    DCHECK_EQ(dporodt_shape.dims(), 2);
    DCHECK_EQ(pt_shape.dims(), 2);
    DCHECK_EQ(perm_shape.dims(), 2);
    DCHECK_EQ(poro_shape.dims(), 2);
    DCHECK_EQ(qw_shape.dims(), 2);
    DCHECK_EQ(qo_shape.dims(), 2);
    DCHECK_EQ(muw_shape.dims(), 2);
    DCHECK_EQ(muo_shape.dims(), 2);
    DCHECK_EQ(sref_shape.dims(), 2);
    DCHECK_EQ(dt_shape.dims(), 0);
    DCHECK_EQ(h_shape.dims(), 0);

    // extra check
    // int m = Example.dim_size(0);
        
    // create output shape
    
    TensorShape grad_s0_shape(s0_shape);
    TensorShape grad_dporodt_shape(dporodt_shape);
    TensorShape grad_pt_shape(pt_shape);
    TensorShape grad_perm_shape(perm_shape);
    TensorShape grad_poro_shape(poro_shape);
    TensorShape grad_qw_shape(qw_shape);
    TensorShape grad_qo_shape(qo_shape);
    TensorShape grad_muw_shape(muw_shape);
    TensorShape grad_muo_shape(muo_shape);
    TensorShape grad_sref_shape(sref_shape);
    TensorShape grad_dt_shape(dt_shape);
    TensorShape grad_h_shape(h_shape);
            
    // create output tensor
    
    Tensor* grad_s0 = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, grad_s0_shape, &grad_s0));
    Tensor* grad_dporodt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(1, grad_dporodt_shape, &grad_dporodt));
    Tensor* grad_pt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(2, grad_pt_shape, &grad_pt));
    Tensor* grad_perm = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(3, grad_perm_shape, &grad_perm));
    Tensor* grad_poro = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(4, grad_poro_shape, &grad_poro));
    Tensor* grad_qw = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(5, grad_qw_shape, &grad_qw));
    Tensor* grad_qo = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(6, grad_qo_shape, &grad_qo));
    Tensor* grad_muw = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(7, grad_muw_shape, &grad_muw));
    Tensor* grad_muo = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(8, grad_muo_shape, &grad_muo));
    Tensor* grad_sref = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(9, grad_sref_shape, &grad_sref));
    Tensor* grad_dt = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(10, grad_dt_shape, &grad_dt));
    Tensor* grad_h = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(11, grad_h_shape, &grad_h));
    
    // get the corresponding Eigen tensors for data access
    
    auto s0_tensor = s0.flat<double>().data();
    auto dporodt_tensor = dporodt.flat<double>().data();
    auto pt_tensor = pt.flat<double>().data();
    auto perm_tensor = perm.flat<double>().data();
    auto poro_tensor = poro.flat<double>().data();
    auto qw_tensor = qw.flat<double>().data();
    auto qo_tensor = qo.flat<double>().data();
    auto muw_tensor = muw.flat<double>().data();
    auto muo_tensor = muo.flat<double>().data();
    auto sref_tensor = sref.flat<double>().data();
    auto dt_tensor = dt.flat<double>().data();
    auto h_tensor = h.flat<double>().data();
    auto grad_sat_tensor = grad_sat.flat<double>().data();
    auto sat_tensor = sat.flat<double>().data();
    auto grad_s0_tensor = grad_s0->flat<double>().data();
    auto grad_dporodt_tensor = grad_dporodt->flat<double>().data();
    auto grad_pt_tensor = grad_pt->flat<double>().data();
    auto grad_perm_tensor = grad_perm->flat<double>().data();
    auto grad_poro_tensor = grad_poro->flat<double>().data();
    auto grad_qw_tensor = grad_qw->flat<double>().data();
    auto grad_qo_tensor = grad_qo->flat<double>().data();
    auto grad_muw_tensor = grad_muw->flat<double>().data();
    auto grad_muo_tensor = grad_muo->flat<double>().data();
    auto grad_sref_tensor = grad_sref->flat<double>().data();
    auto grad_dt_tensor = grad_dt->flat<double>().data();
    auto grad_h_tensor = grad_h->flat<double>().data();   

    // implement your backward function here 

    // TODO:
    
  }
};
REGISTER_KERNEL_BUILDER(Name("SaturationGrad").Device(DEVICE_GPU), SaturationGradOpGPU);

#endif