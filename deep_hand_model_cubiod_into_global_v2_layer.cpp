#include <algorithm>
#include "caffe/layer.hpp"
#include "caffe/deep_hand_model_layers.hpp"
namespace caffe {

    template <typename Dtype>
    void DeepHandModelCubiodIntoGlobalV2Layer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
    }

    template <typename Dtype>
    void DeepHandModelCubiodIntoGlobalV2Layer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top_shape.resize(axis + 1);
        top_shape[axis] = JointNum * 3;
        top[0]->Reshape(top_shape);
    }

    template <typename Dtype>
    void DeepHandModelCubiodIntoGlobalV2Layer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const Dtype* joint_3d_data = bottom[0]->cpu_data();
        const Dtype* x_lb_data = bottom[1]->cpu_data();
        const Dtype* x_ub_data = bottom[2]->cpu_data();
        const Dtype* y_lb_data = bottom[3]->cpu_data();
        const Dtype* y_ub_data = bottom[4]->cpu_data();
        const Dtype* z_lb_data = bottom[5]->cpu_data();
        const Dtype* z_ub_data = bottom[6]->cpu_data();

        Dtype* top_data = top[0]->mutable_cpu_data();
        const int batSize = (bottom[0]->shape())[0];
        for (int t = 0; t < batSize; t++) {
            double x_lb = x_lb_data[t];
            double x_ub = x_ub_data[t];
            double y_lb = y_lb_data[t];
            double y_ub = y_ub_data[t];
            double z_lb = z_lb_data[t];
            double z_ub = z_ub_data[t];


            for (int i = 0; i < JointNum; i++) {
                int Bid = t * JointNum * 3;
                double global_x = (joint_3d_data[Bid + i * 3] + 1.0) / 2.0 * (x_ub - x_lb) + x_lb;
                double global_y = (-joint_3d_data[Bid + i * 3 + 1] + 1.0) / 2.0 * (y_ub - y_lb) + y_lb;
                double global_z = (-joint_3d_data[Bid + i * 3 + 2] + 1.0) / 2.0 * (z_ub - z_lb) + z_lb;
                //Note the negative sign 

                int Tid = t * JointNum * 3;
                top_data[Tid + i * 3] = global_x;
                top_data[Tid + i * 3 + 1] = global_y;
                top_data[Tid + i * 3 + 2] = global_z;
            }

        }
    }


    template <typename Dtype>
    void DeepHandModelCubiodIntoGlobalV2Layer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down,
        const vector<Blob<Dtype>*>& bottom) {

    }

#ifdef CPU_ONLY
    STUB_GPU(DeepHandModelCubiodIntoGlobalV2Layer);
#endif

    INSTANTIATE_CLASS(DeepHandModelCubiodIntoGlobalV2Layer);
    REGISTER_LAYER_CLASS(DeepHandModelCubiodIntoGlobalV2);
}  // namespace caffe
