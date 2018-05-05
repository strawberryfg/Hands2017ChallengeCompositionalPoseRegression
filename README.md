# Hands2017ChallengeCompositionalPoseRegression
Implementation of Compositional Pose Regression for ICCV2017 workshop Hands2017 Challenge.

Note that this is the unofficial implementation for the paper "Compositional Human Pose Regression", and thus the author does not guarantee the 100 percent accuracy.

In case it is beneficial for your research, please cite this wepage.

The author finds it laborious to upload the preprocessed depth data & ground truth & statistics(avg & std), and to write decent comments for the code. Data is on Google Drive: https://drive.google.com/open?id=1jHALBXnf-XXlJiwAuRoLqVQ-9qMmU6ku 

Train:

......missing_index.txt: missing index (invalid images) index starting from 1

......subbg_v0_xiaotao_hands_train_meanscale180\subbg_v0_xiaotao_hands_train_meanscale180:

                                                         processed image source 1 (943401 cropped images)
                                                         
......subbg_v0_xiaotao_hands_train_meanscale200\subbg_v0_xiaotao_hands_train_meanscale200:

                                                         processed image source 2 (943401 cropped images)
                                                         
                                                         another cropping strategy with minor difference)
                                                         
......train_bbx_1101_meanscale180\bbx_1101_meanscale180: bbx of preprocessed image source 1 

                                                         Format: (bbx_x1, bbx_y1, width, height)
                                                         
......train_bbx_1101_meanscale200\bbx_1101_meanscale200: bbx of preprocessed image source 2 

......train_gt_joint_3d_local_1101_meanscale180\gt_joint_3d_local_1101_meanscale180:

                                                         local 3d joint within the 400*400*400 cube ; normalized in [-1, 1] ; 21 * 3 dimension
                                                         ......train_gt_joint_3d_local_1101_meanscale200\gt_joint_3d_local_1101_meanscale200:
                                                         
                                                         local 3d joint 
                                                         
......train_gt_centroid_qf_1101_meanscale180\gt_centroid_qf_1101_meanscale180 :

                                                         ground centroid x y z (global coordinate) 3 dimension
                                                         
......train_gt_centroid_qf_1101_meanscale200\gt_centroid_qf_1101_meanscale200 :                                                         

......stdavg_gt_0824.zip:                                

                                                         standard deviation / average statistics on the bone length of the dataset


Test:

......subbg_v0_xiaotao_hands_test_meanscale180\subbg_v0_xiaotao_hands_train_meanscale180:

                                                         processed image source 1 (943401 cropped images)
                                                         
......subbg_v0_xiaotao_hands_tEst_meanscale200\subbg_v0_xiaotao_hands_train_meanscale200:

                                                         processed image source 2 (943401 cropped images)
                                                         
                                                         another cropping strategy with minor difference)
                                                         
......test_bbx_1101_meanscale180\bbx_1101_meanscale180: bbx of preprocessed image source 1 

                                                         Format: (bbx_x1, bbx_y1, width, height)
                                                         
......test_bbx_1101_meanscale200\bbx_1101_meanscale200: bbx of preprocessed image source 2 

......test_gt_centroid_qf_1101_meanscale180\gt_centroid_qf_1101_meanscale180 :

                                                         ground centroid x y z (global coordinate) 3 dimension
                                                         
......test_gt_centroid_qf_1101_meanscale200\gt_centroid_qf_1101_meanscale200 :                                                         

Good luck!

@inproceedings{sun2017compositional,
  title={Compositional human pose regression},
  author={Sun, Xiao and Shang, Jiaxiang and Liang, Shuang and Wei, Yichen},
  booktitle={The IEEE International Conference on Computer Vision (ICCV)},
  volume={2},
  year={2017}
}

@article{yuan20173d,
  title={3D Hand Pose Estimation: From Current Achievements to Future Goals},
  author={Yuan, Shanxin and Garcia-Hernando, Guillermo and Stenger, Bjorn and Moon, Gyeongsik and Chang, Ju Yong and Lee, Kyoung Mu and Molchanov, Pavlo and Kautz, Jan and Honari, Sina and Ge, Liuhao and others},
  journal={arXiv preprint arXiv:1712.03917},
  year={2017}
}
