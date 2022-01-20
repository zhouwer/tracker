# tracker
yolov5-deepsort+opencv.kcf+TensorRT+QT

第一篇博客，可能格式不会太规范，就是记录一下。现在工作主要是cv算法部署英伟达开发板加算法开发，由于工作需求做了一个界面，
在基于deepsort的基础上加入了临时绘制跟踪目标的功能，并行运行kcf跟踪，update失败后自动删除，可以实时显示坐标，具有把位置信息传送到下位机的功能，
主要是跟着以下两位大佬的项目做的：

https://github.com/RichardoMrMu/yolov5-deepsort-tensorrt

https://github.com/wang-xinyu/tensorrtx/

环境的话上两篇博客项目中都有，qt使用的是qt creator，我是在终端直接编译的，参照下边这篇博客改了一下cmakelists，

https://blog.csdn.net/qq_42823342/article/details/120799577

其他的没有了。

