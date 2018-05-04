import numpy as np
from skimage import measure,data,color
from skimage.morphology import disk
import skimage.filters.rank as sfr
#图像处理的辅助工具库
from PIL import Image,ImageDraw,ImageEnhance
#import mlab as mlab
import matplotlib as mat
import matplotlib.pyplot as plt


#基于数学形态学的车牌粗定位算法
#图像采集设备获取的车辆图像质量往往不符合要求需要进行图像预处理操作
#获取原始图像

img = Image.open('./car.jpg')

#读取图片并转为数组
im = np.array(img)



#输出数组的各维度长度以及类型
print(im.shape)
print(im.dtype)

#输出位于坐标100,100，颜色通道为r的像素值
print (im[100,100,0])


plt.figure(num=1,figsize=(5,5),dpi=96) #设置窗口大小

'''
要理解照片直方图，
绕不开“亮度”这个概念。
人们把照片的亮度分为0到255共256个数值，数值越大，代表的亮度越高。
其中0代表纯黑色的最暗区域，255表示最亮的纯白色，
而中间的数字就是不同亮度的灰色。
人们还进一步把这些亮度分为了5个区域，
分别是黑色，阴影，中间调，高光和白色。



这里打印的是图片直方图的信息 不是位图bmp信息
当我们用横轴代表0-255的亮度数值。
竖轴代表照片中对应亮度的像素数量，
这个函数图像就被称为直方图。



直方图中柱子的高度，代表了画面中有多少像素是那个亮度，
其实就可以看出来画面中亮度的分布和比例。
比如下面一个直方图，
波峰是在中间偏左的位置（阴影区域），
说明画面中有很多深灰或者深色部分。



上面的这个直方图
准确来说应该叫RGB直方图，
因为他是由红、绿、蓝三个通道的直方图叠加后除以3而成的。
我们知道色彩是由红、绿、蓝三原色混合而成。而相机记录照片的时候，
也是分别记录下了红、绿、蓝每个“通道”下的版本，
最后再混合成一张五颜六色的照片。
在相机的照片预览模式中，
我们可以同时看到R（红）、G（绿）、B（蓝）每个通道的直方图，
以及最上面叠加后的RGB直方图。
'''

plt.subplot(2,1,1)
ar=im[:,:,0].flatten()
#hold=1
plt.hist(ar, bins=256, normed=1,facecolor='r',edgecolor='r')
ag=im[:,:,1].flatten()
plt.hist(ag, bins=256, normed=1, facecolor='g',edgecolor='g')
ab=im[:,:,2].flatten()
plt.hist(ab, bins=256, normed=1, facecolor='b',edgecolor='b')

#红色通道
r = im[:,:,0]

#交换红蓝通道并显示
im[:,:,0] = im[:,:,2]

im[:,:,2] = r
plt.subplot(2,1,2)
plt.suptitle('exchange RGB') # 图片名称
plt.imshow(im)



#figsize 左边宽度 右边 高度
plt.figure(num=2,figsize=(12,8),dpi=96) #设置窗口大小

row = 3

column = 3

plt.suptitle('Multi_Image1') # 图片名称

plt.subplot(row,column,1)
plt.title('source image')
plt.imshow(img)
plt.axis('off')

#获取原始图像的直方图

arr = img.histogram()

plt.subplot(row,column,2)
plt.title('source zhi fang tu')
n, bins, patches = plt.hist(arr, bins=256, normed=0,edgecolor='None',facecolor='red')
print("直方图向量")
print(n)
print("各个bin的区间范围")
print(bins)
print("每个bin里面包含的数据，是一个list")
print(patches)
print(patches[0])
print(patches[1])

'''
目前图像采集设备的分辨率普遍较高，拍摄出来的图像一般都较大，
为了保证系统的实时性，提高系统运算速度，必须缩小图像的尺寸，
本系统最好的图像输入尺寸是简单有效的车牌定位算法（附源码和详细解析），
所以，以图像的高度简单有效的车牌定位算法（附源码和详细解析）为一个阈值，
当图像高度简单有效的车牌定位算法（附源码和详细解析）时，
取图像的压缩率简单有效的车牌定位算法（附源码和详细解析），
以此使车辆图像得到合理压缩。
'''

#图像压缩

print('source img Width')
print(img.width)
print('source img Height')
print(img.height)


imgCompress = img.resize((128,128),Image.BILINEAR)

plt.subplot(row,column,3)

plt.title('compress image')

plt.imshow(imgCompress)

'''
彩色图像含有大量彩色信息，占据存储空间较多，
运算起来速度较慢，实时性差，
所以，可以对彩色图像进行降维处理，也就是灰度转换
RGB彩色图像灰度转换。
由第3章RGB彩色模型相关知识知道，
RGB彩色图像在MATLAB中是
以3个0至255灰度级的灰度矩阵按一定比例构成。


'''
#灰度图

'''
将当前图像转换为其他模式，并且返回新的图像。

当从一个调色板图像转换时，这个方法通过这个调色板来转换像素。
如果不对变量mode赋值，该方法将会选择一种模式，
在没有调色板的情况下，
使得图像和调色板中的所有信息都可以被表示出来。

当从一个颜色图像转换为黑白图像时，PIL库使用ITU-R601-2 luma转换公式：

L = R * 299/1000 + G * 587/1000 + B * 114/1000

当转换为2位图像（模式“1”）时，源图像首先被转换为黑白图像。
结果数据中大于127的值被设置为白色，其他的设置为黑色；
这样图像会出现抖动。如果要使用其他阈值，更改阈值127，
可以使用方法point()。为了去掉图像抖动现象，
'''
imgGray = np.array(imgCompress.convert('L'))
im2 = 255 - imgGray                 # 对图像进行反相处理

im3 = (100.0/255) * imgGray + 100    # 将图像像素值变换到 100...200 区间

im4 = 255.0 * (imgGray/255.0)**2     # 对图像像素值求平方后得到的图像(二次函数变换，使较暗的像素值变得更小)

plt.subplot(row,column,4)

plt.title('gray1 image')

#显示灰度图 要加参数 cmap

plt.imshow(imgGray,cmap='gray')

#灰度图直方图
#arr = np.array(imgCompress.convert('L').histogram()).flatten()
#其中的flatten()函数是numpy包里面的，用于将二维数组序列化成一维数组。
# 前一个数组是直方图的统计量，后一个数组是每个bin的中间值
arr = imgCompress.convert('L').histogram()
plt.subplot(row,column,5)
plt.title('gray zhi fang tu')
'''
arr: 需要计算直方图的一维数组

bins: 直方图的柱数，可选项，默认为10

normed: 是否将得到的直方图向量归一化。默认为0

facecolor: 直方图颜色

edgecolor: 直方图边框颜色

alpha: 透明度

histtype: 直方图类型，‘bar’, ‘barstacked’, ‘step’, ‘stepfilled’

返回值 ：

n: 直方图向量，是否归一化由参数normed设定

bins: 返回各个bin的区间范围

patches: 返回每个bin里面包含的数据，是一个list
'''

#这里的 直方图 没有均衡化 处理 等 
n, bins, patches = plt.hist(arr, bins=256, normed=1,edgecolor='None',facecolor='red')
print("直方图向量")
print(n)
print("各个bin的区间范围")
print(bins)
print("每个bin里面包含的数据，是一个list")
print(patches)
print(patches[0])
print(patches[1])

plt.subplot(row,column,7)

plt.title('f(x) = 255 - x')

#显示灰度图 要加参数 cmap

plt.imshow(im2,cmap='gray')

plt.subplot(row,column,8)

plt.title('f(x) = (100/255)*x + 100')

#显示灰度图 要加参数 cmap

plt.imshow(im3,cmap='gray')

plt.subplot(row,column,9)

plt.title('f(x) =255 *(x/255)^2')

#显示灰度图 要加参数 cmap

plt.imshow(im4,cmap='gray')



#注意 以上所有的图片展示区域设置后 最后统一 调用这个 展示

# 灰度拉伸 暂时 不做 灰度拉伸 标准解释

# 图像局部增强1

'''
图像局部增强，突出车牌区域。
该步骤主要采用了数学形态学中的开运算，
先腐蚀后膨胀操作，消除背景噪声并采用简单的图像代数运算——减运算，
突出车牌区域。先对第3步灰度拉伸后的图像I1作开运算处理，
得到非目标区域的背景图像I2，
再让图像I1减去I2得到突出车牌目标区域后的图像。
'''

'''
开运算和闭运算就是将腐蚀和膨胀按照一定的次序进行处理。
但这两者并不是可逆的，即先开后闭并不能得到原先的图像。

闭运算用来连接被误分为许多小块的对象，
而开运算用于移除由图像噪音形成的斑点。

1. 腐蚀是一种消除边界点，使边界向内部收缩的过程。
可以用来消除小且无意义的物体。
腐蚀的算法：
用3x3的结构元素，扫描图像的每一个像素
用结构元素与其覆盖的二值图像做“与”操作
如果都为1，结果图像的该像素为1。否则为0。
结果：使二值图像减小一圈


2. 膨胀是将与物体接触的所有背景点合并到该物体中，使边界向外部扩张的过程。
可以用来填补物体中的空洞。
膨胀的算法：
用3x3的结构元素，扫描图像的每一个像素
用结构元素与其覆盖的二值图像做“与”操作
如果都为0，结果图像的该像素为0。否则为1
结果：使二值图像扩大一圈


3. 先腐蚀后膨胀的过程称为开运算。
用来消除小物体、在纤细点处分离物体、平滑较大物体的边界的同时并不明显改变其面积。


4. 先膨胀后腐蚀的过程称为闭运算。
用来填充物体内细小空洞、连接邻近物体、平滑其边界的同时并不明显改变其面积。
'''


'''
autolevel

这个词在photoshop里面翻译成自动色阶，
用局部直方图来对图片进行滤波分级。

该滤波器局部地拉伸灰度像素值的直方图，以覆盖整个像素值范围。
'''
# 图像局部增强2
plt.figure(num=3,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('base filters')
img =color.rgb2gray(np.array(Image.open('./car.jpg')))
auto =sfr.autolevel(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(121)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(122)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)

plt.figure(num=4,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('bi yun suan')
#bottomhat: 此滤波器先计算图像的形态学闭运算，
#然后用原图像减去运算的结果值，有点像黑帽操作
img =color.rgb2gray(np.array(Image.open('./car.jpg')))
auto =sfr.bottomhat(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(121)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(122)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)

plt.figure(num=5,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('kai yun suan')
# 此滤波器先计算图像的形态学开运算，
#然后用原图像减去运算的结果值，有点像白帽操作
img =color.rgb2gray(np.array(Image.open('./car.jpg')))
auto =sfr.tophat(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(121)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(122)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)



#图像二值化

 #  setup a converting table with constant threshold 
threshold  =   80 
table  =  []
for  i  in  range( 256 ):
	if  i  <  threshold:
		table.append(0)
	else:
		table.append( 1 )

# 灰度图
#  convert to grey level image 

#  convert to binary image by the table 

imH = Image.fromarray(auto)

bim  =  imH.point(table,'1')

plt.figure(num=6,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('er zhi hua')
plt.imshow(bim,plt.cm.gray)

#bim.save("erzhihua_img.jpg")


#边缘检测
'''
边缘检测，获取牌照以及字符的轮廓。
对比其他边缘检测算子，本系统选用了对弱边缘有较精确的提取能力，
同时又能较大程度保留车牌轮廓纹理的Canny算子，
由本文第三章知道Canny边缘检测算子主要实现步骤有四：
首先用高斯滤波器平滑预处理前小节二值化后的车辆图像简单有效的车牌定位算法
（附源码和详细解析），消除部分噪声，
然后使用梯度工具，
计算前一步骤作用后的图像简单有效的车牌定位算法（附源码和详细解析）、
简单有效的车牌定位算法（附源码和详细解析）方向的梯度并用公式3.17
得到幅值和方向角，之后采用非极大值抑制(NMS)方法细化梯度幅值（
另一种说法，模），缩小方向角θ，最终使用双阈值法定位并提取出边缘。
'''

#对得到二值图像进行边缘检测和开闭操作进行数字形态学处理
plt.figure(num=7,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('bian yuan jian ce')

img =color.rgb2gray(np.array(bim))
auto =sfr.bottomhat(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(321)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(322)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)

img =color.rgb2gray(auto)
auto =sfr.bottomhat(img, disk(5))  #半径为5的圆形滤波器

plt.subplot(323)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(324)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)

img =color.rgb2gray(auto)
auto =sfr.tophat(img, disk(5))  #半径为5的圆形滤波器

plt.subplot(325)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(326)
plt.title('filted image')
plt.imshow(auto,plt.cm.gray)



#检测所有图形的轮廓
contours = measure.find_contours(auto, 0.5)


#绘制轮廓
fig, axes = plt.subplots(1,2,figsize=(8,8))#设置窗口大小
plt.suptitle('bian yuan jian ce2')
ax0, ax1= axes.ravel()
ax0.imshow(auto,plt.cm.gray)
ax0.set_title('original image')

rows,cols=img.shape
ax1.axis([0,rows,cols,0])
for n, contour in enumerate(contours):
    ax1.plot(contour[:, 1], contour[:, 0], linewidth=2)
ax1.axis('image')
ax1.set_title('contours')

plt.show()
