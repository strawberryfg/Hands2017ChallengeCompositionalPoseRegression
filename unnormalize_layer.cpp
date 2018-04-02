#include <algorithm>
#include "caffe/layer.hpp"
#include "caffe/operations.hpp"
namespace caffe {

    template <typename Dtype>
    void UnnormalizeLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
    }

    template <typename Dtype>
    void UnnormalizeLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const int axis = bottom[0]->CanonicalAxisIndex(
            this->layer_param_.inner_product_param().axis());
        vector<int> top_shape = bottom[0]->shape();
        top[0]->Reshape(top_shape);
    }


    template <typename Dtype>
    void UnnormalizeLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
        const vector<Blob<Dtype>*>& top) {
        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* std_data = bottom[1]->cpu_data(); //standard deviation
        const Dtype* avg_data = bottom[2]->cpu_data(); //mean value average
        Dtype* top_data = top[0]->mutable_cpu_data();
        const int batSize = (bottom[0]->shape())[0];
        const int dimSize = (bottom[0]->shape())[1]; //2 dimensions
        for (int t = 0; t < batSize; t++) {
            for (int i = 0; i < dimSize; i++) {
                int Tid = t * dimSize, Bid = t * dimSize;
                double std_value = std_data[Bid + i];
                double avg_value = avg_data[Bid + i];
                top_data[Tid + i] = bottom_data[Bid + i] * std_value + avg_value; //multiplied by the std of that dimension and plus the average mean value				
            }
        }
    }


    template <typename Dtype>
    void UnnormalizeLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
        const vector<bool>& propagate_down,
        const vector<Blob<Dtype>*>& bottom) {

        const Dtype* bottom_data = bottom[0]->cpu_data();
        const Dtype* std_data = bottom[1]->cpu_data(); //standard deviation
        const Dtype* avg_data = bottom[2]->cpu_data(); //mean value average
        const Dtype* top_diff = top[0]->cpu_diff();
        Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();

        const int batSize = (bottom[0]->shape())[0];
        const int dimSize = (bottom[0]->shape())[1]; //2 dimensions
        for (int t = 0; t < batSize; t++) {
            for (int i = 0; i < dimSize; i++) {
                int Tid = t * dimSize, Bid = t * dimSize;
                double std_value = std_data[Bid + i];
                bottom_diff[Bid + i] = top_diff[Tid + i] * std_value;
            }
        }
    }

#ifdef CPU_ONLY
    STUB_GPU(UnnormalizeLayer);
#endif

    INSTANTIATE_CLASS(UnnormalizeLayer);
    REGISTER_LAYER_CLASS(Unnormalize);
}  // namespace caffe
