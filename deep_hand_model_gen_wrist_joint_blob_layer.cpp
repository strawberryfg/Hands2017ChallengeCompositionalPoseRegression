#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

namespace caffe {

	template <typename Dtype>
	void DeepHandModelGenWristJointBlobLayer<Dtype>::LayerSetUp(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {

	}
	template <typename Dtype>
	void DeepHandModelGenWristJointBlobLayer<Dtype>::Reshape(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
		const int axis = bottom[0]->CanonicalAxisIndex(
			this->layer_param_.inner_product_param().axis());
		vector<int> top_shape = bottom[0]->shape();
		top_shape.resize(axis + 1);
		top_shape[axis] = JointNum * 3;
		top[0]->Reshape(top_shape);
	}

	template <typename Dtype>
	void DeepHandModelGenWristJointBlobLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top) {
		int batSize = (bottom[0]->shape())[0];
		const Dtype* bottom_data = bottom[0]->cpu_data();
		Dtype* top_data = top[0]->mutable_cpu_data();
		for (int t = 0; t < batSize; t++) {
			int Bid = t * 3, Tid = t * JointNum * 3;
			for (int j = 0; j < JointNum * 3; j++) top_data[Tid + j] = 0.0;
			for (int j = 0; j < JointNum; j++) {
				for (int k = 0; k < 3; k++) {
					top_data[Tid + j * 3 + k] = -1.0 * bottom_data[Bid + wrist * 3 + k];
					//all joint add the offset of Wrist(which is the opposite of bone(Jorigin-JWrist)
				}
			}
		}
	}

	template <typename Dtype>
	void DeepHandModelGenWristJointBlobLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
		const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
		int batSize = (bottom[0]->shape())[0];
		const Dtype* bottom_data = bottom[0]->cpu_data();
		const Dtype* top_diff = top[0]->cpu_diff();
		Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
		if (propagate_down[0]) {
			for (int t = 0; t < batSize; t++) {
				int Bid = t * 3;
				for (int j = 0; j < 3; j++) {
					bottom_diff[Bid + j] = 0;
				}
				for (int j = 0; j < JointNum; j++) {
					for (int k = 0; k < 3; k++) {
						int Tid = t * JointNum * 3;
						bottom_diff[Bid + k] += -1.0 * top_diff[Tid + j * 3 + k];
					}
				}
			}
		}
	}

#ifdef CPU_ONLY
	STUB_GPU(DeepHandModelGenWristJointBlobLayer);
#endif

	INSTANTIATE_CLASS(DeepHandModelGenWristJointBlobLayer);
	REGISTER_LAYER_CLASS(DeepHandModelGenWristJointBlob);
}