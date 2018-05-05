#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/deep_hand_model_layers.hpp"

using namespace cv;
//#define _DEBUG
namespace caffe {

	template <typename Dtype>
	void DeepHandModelReadDepthNoBBXWithAVGZLayer<Dtype>::LayerSetUp(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
		depth_size_ = this->layer_param_.read_depth_no_bbx_with_avgz_param().depth_size();
		file_prefix_ = this->layer_param_.read_depth_no_bbx_with_avgz_param().file_prefix();

	}
	template <typename Dtype>
	void DeepHandModelReadDepthNoBBXWithAVGZLayer<Dtype>::Reshape(
		const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
		vector<int> top_shape;
		top_shape.push_back((bottom[0]->shape())[0]);
		top_shape.push_back(3);
		top_shape.push_back(depth_size_);
		top_shape.push_back(depth_size_);
		top[0]->Reshape(top_shape);
	}

	template <typename Dtype>
	void DeepHandModelReadDepthNoBBXWithAVGZLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
		const vector<Blob<Dtype>*>& top)
	{
		int batSize = (bottom[0]->shape())[0];
		const Dtype* index_data = bottom[0]->cpu_data();  //index        
		const Dtype* avgz_data = bottom[1]->cpu_data(); //z of centroid
		Dtype* depth_data = top[0]->mutable_cpu_data(); //depth        
		for (int t = 0; t < batSize; t++)
		{
			int index = (int)index_data[t];
			char depthfile[maxlen];
			sprintf(depthfile, "%s%08d%s", file_prefix_.c_str(), index, ".png");
			Mat depth = imread(depthfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
			Mat norm_depth = Mat::zeros(Size(depth.cols, depth.rows), CV_8UC3);
			
			double avg_d = avgz_data[t];
			
			for (int row = 0; row < depth.rows; row++)
			{
				for (int col = 0; col < depth.cols; col++)
				{
					int cur_d = depth.at<ushort>(row, col);
					if (cur_d && cur_d >= depth_lb && cur_d <= depth_ub)
					{
						int cur_col = (-(double(cur_d - avg_d) / double(100.0)) + 1.0) / 2.0 * 255;
						//<avg_d e.g. -1    -> (1+1)/2=1.0   
						norm_depth.at<Vec3b>(row, col)[0] = norm_depth.at<Vec3b>(row, col)[1] = norm_depth.at<Vec3b>(row, col)[2] = cur_col;
					}
				}
			}

			resize(norm_depth, norm_depth, Size(depth_size_, depth_size_));

			for (int row = 0; row < depth_size_; row++)
			{
				for (int col = 0; col < depth_size_; col++)
				{
					for (int c = 0; c < 3; c++)
					{
						int Tid = t * 3 * depth_size_ * depth_size_;
						depth_data[Tid + c * depth_size_ * depth_size_ + row * depth_size_ + col] = norm_depth.at<Vec3b>(row, col)[c];
					}

				}
			}

		}
	}

	template <typename Dtype>
	void DeepHandModelReadDepthNoBBXWithAVGZLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
		const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {

	}

#ifdef CPU_ONLY
	STUB_GPU(DeepHandModelReadDepthNoBBXWithAVGZLayer);
#endif

	INSTANTIATE_CLASS(DeepHandModelReadDepthNoBBXWithAVGZLayer);
	REGISTER_LAYER_CLASS(DeepHandModelReadDepthNoBBXWithAVGZ);
}
