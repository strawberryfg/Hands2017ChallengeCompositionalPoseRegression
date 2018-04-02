#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

namespace caffe {

	template <typename Dtype>
	void DeepHandModelGenNegWristBlobLayer<Dtype>::LayerSetUp(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {

	}
	template <typename Dtype>
	void DeepHandModelGenNegWristBlobLayer<Dtype>::Reshape(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
		const int axis = bottom[0]->CanonicalAxisIndex(
			this->layer_param_.inner_product_param().axis());
		vector<int> top_shape = bottom[0]->shape();
		top_shape.resize(axis + 1);
		top_shape[axis] = 3;
		top[0]->Reshape(top_shape);
	}

	template <typename Dtype>
	void DeepHandModelGenNegWristBlobLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top) {
		int batSize = (bottom[0]->shape())[0];
		const Dtype* bottom_data = bottom[0]->cpu_data();
		Dtype* top_data = top[0]->mutable_cpu_data();
		for (int t = 0; t < batSize; t++) {
			int Bid = t * JointNum * 3, Tid = t * 3;
			for (int j = 0; j < 3; j++) top_data[Tid + j] = -1.0 * bottom_data[Bid + wrist * 3 + j];
		}
	}

	template <typename Dtype>
	void DeepHandModelGenNegWristBlobLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
		const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
		int batSize = (bottom[0]->shape())[0];
		const Dtype* bottom_data = bottom[0]->cpu_data();
		const Dtype* top_diff = top[0]->cpu_diff();
		Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
		if (propagate_down[0]) {
			for (int t = 0; t < batSize; t++) {
				int Bid = t * JointNum * 3;
				for (int j = 0; j < JointNum * 3; j++) bottom_diff[Bid + j] = 0.0;
				for (int j = 0; j < 3; j++) {
					int Tid = t * 3;
					bottom_diff[Bid + wrist * 3 + j] = top_diff[Tid + j] * (-1.0); //because of direct copy
				}
			}
		}
	}

#ifdef CPU_ONLY
	STUB_GPU(DeepHandModelGenNegWristBlobLayer);
#endif

	INSTANTIATE_CLASS(DeepHandModelGenNegWristBlobLayer);
	REGISTER_LAYER_CLASS(DeepHandModelGenNegWristBlob);
}