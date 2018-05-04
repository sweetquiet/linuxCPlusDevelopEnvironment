import numpy as np
from numpy.linalg import cholesky
from skimage import measure,data,color
from skimage.morphology import disk,square,rectangle
import skimage.morphology as openclose
import skimage.filters.rank as sfr
from skimage import img_as_float, img_as_ubyte
#图像处理的辅助工具库
from PIL import Image,ImageDraw,ImageEnhance
#import mlab as mlab
import matplotlib as mat
import matplotlib.mlab as mlab 
import matplotlib.pyplot as plt
import scipy.signal as signal


#https://blog.csdn.net/u013378306/article/details/70156842?locationNum=1&fps=1

#基于数学形态学的车牌粗定位算法
#图像采集设备获取的车辆图像质量往往不符合要求需要进行图像预处理操作
#获取原始图像

img = Image.open('./car.jpg')
'''
为了保证三个通道 我们这里需要指定图片模式 
方便操作
1，L，P，RGB，RGBA，CMYK，YCbCr，I，F。
'''
img = img.convert('RGB')
#读取图片并转为数组
im = np.array(img)



#输出数组的各维度长度以及类型
print(im.shape)
print(im.dtype)

# 获取图像的维度，行数，列数以及通道数
rowBins, colBins, channel=im.shape
print('图像的维度，行数，列数以及通道数')
print(rowBins)
print(colBins)
print(channel)
# 图像的尺寸
print('source img Width')
print(img.width)
print('source img Height')
print(img.height)
# 求图像的最大值，最小值，均值
print('图像的最大值，最小值，均值')
print(im.max())
print(im.min())
print(im.mean())


#输出位于坐标100,100，颜色通道为r的像素值

print('输出位于坐标100,100，颜色通道为r的像素值')
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

column = 4

plt.suptitle('Multi_Image1') # 图片名称

plt.subplot(row,column,1)
plt.title('source image')
plt.imshow(img)
plt.axis('off')

#获取原始图像的直方图

#arr = img.histogram()

#彩色直方图只能叠加
plt.subplot(row,column,2)
plt.title('source zhi fang tu')
#https://blog.csdn.net/icamera0/article/details/50683106
r,g,b=img.split()

ar=np.array(r).flatten()
plt.hist(ar, bins=256, normed=1,facecolor='r',edgecolor='r')
ag=np.array(g).flatten()
plt.hist(ag, bins=256, normed=1, facecolor='g',edgecolor='g')
ab=np.array(b).flatten()

n, bins, patches = plt.hist(ab, bins=256, normed=1, facecolor='b',edgecolor='b')
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

#im4 = 255.0 * (imgGray/255.0)**2     # 对图像像素值求平方后得到的图像(二次函数变换，使较暗的像素值变得更小)

maxL = imgGray.max()

minL = imgGray.min()

im4 = (255.0/(maxL - minL))*imgGray - (255*minL)/(maxL-minL)

plt.subplot(row,column,5)

plt.title('gray1 image')

#显示灰度图 要加参数 cmap

plt.imshow(imgGray,cmap='gray')

#灰度图直方图
#arr = np.array(imgCompress.convert('L').histogram()).flatten()
#其中的flatten()函数是numpy包里面的，用于将二维数组序列化成一维数组。

#arr = np.histogram(a=np.array(imgCompress.convert('L')).flatten(),bins=rowBins,normed=False)
arr = np.array(imgCompress.convert('L')).flatten()
plt.subplot(row,column,6)
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

#这里的 直方图 没有均衡化 处理 等 https://www.cnblogs.com/smallpi/p/4550360.html



## 前一个数组是直方图的统计量，后一个数组是每个bin的中间值
n, bins, patches = plt.hist(arr, bins=rowBins, normed=1,edgecolor='None',facecolor='red')
print("直方图向量")
print(n)
print("各个bin的区间范围")
print(bins)
print("每个bin里面包含的数据，是一个list")
print(type(patches))
print(patches)
print(type(patches[0]))
print(patches[0])
print(patches[1])


x = np.arange(255)

# 画出变换函数图像1曲线 反相 f(x) = 255 - x
plt.subplot(row,column,7)
plt.title('f(x) = 255 - x')
plt.plot(x,255-x) 


#显示灰度图1 要加参数 cmap
plt.subplot(row,column,8)
plt.title('f(x) = 255 - x')
plt.imshow(im2,cmap='gray')

# 画出变换函数图像2曲线 f(x) = (100/255)*x + 100
plt.subplot(row,column,9)
plt.title('f(x) = (100/255)*x + 100')
plt.plot(x,(100/255.0)*x+100) 

#显示灰度图变换2 要加参数 cmap
plt.subplot(row,column,10)
plt.title('f(x) = (100/255)*x + 100')
plt.imshow(im3,cmap='gray')


# 画出变换函数图像3曲线 f(x) =255 *(x/255)^2
plt.subplot(row,column,11)
plt.title('f(x) =255 *(x/255)^2')
#plt.plot(x,255*(x/255.0)**2) 

#灰度变换 使用的算法 选择这个
plt.plot(x,(255.0/(maxL - minL))*x - (255*minL)/(maxL-minL))

#显示灰度图3 要加参数 cmap
plt.subplot(row,column,12)
plt.title('f(x) =255 *(x/255)^2')
plt.imshow(im4,cmap='gray')



#注意 以上所有的图片展示区域设置后 最后统一 调用这个 展示
#这里的 直方图 没有均衡化 处理 等 https://www.cnblogs.com/smallpi/p/4550360.html
# 灰度拉伸 暂时 不做 灰度拉伸 标准解释

'''
直方图均衡化是利用直方图的累积函数作为灰度变换函数，对图像进行转换。直方图均衡化可以增强图像的对比度。

累积函数和概率论中的累积分布函数类似。
例如对于还有5个数的序列[1,2,3,4,5],其累积函数含有5个数，
第一个数是1，第二个是1+2=3，……，
第五个数是1+2+3+4+5=15，所以其累积函数是[1,3,6,10,15]。
'''
def histeq(image_array,image_bins=256):
    
    # 将图像矩阵转化成直方图数据，返回元组(频数，直方图区间坐标)
    image_array2,bins = np.histogram(image_array.flatten(),image_bins)

    # 计算直方图的累积函数
    cdf = image_array2.cumsum()

    # 将累积函数转化到区间[0,255]
    cdf = (255.0/cdf[-1])*cdf
    
    # 原图像矩阵利用累积函数进行转化，插值过程
    image2_array = np.interp(image_array.flatten(),bins[:-1],cdf)

    # 返回均衡化后的图像矩阵和累积函数
    return image2_array.reshape(image_array.shape),cdf


im4,cfun= histeq(im4)




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
plt.suptitle('zi dong se jie')

imgS = Image.open('./car.jpg').convert('RGB').convert('L')

# 图像数据类型的转换
imgUByte=img_as_float(imgS)
img =color.rgb2gray(np.array(imgUByte))
auto =sfr.autolevel(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(221)
plt.title('jun heng zhi fang tu')
plt.hist(im4.flatten(),256)


plt.subplot(222)
plt.title('jun heng img')
plt.imshow(im4,plt.cm.gray)

plt.subplot(223)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(224)
plt.title('zi dong se jie image')
plt.imshow(auto,plt.cm.gray)




#闭运算
plt.figure(num=4,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('bi yun suan')
#bottomhat: 此滤波器先计算图像的形态学闭运算，
#然后用原图像减去运算的结果值，有点像黑帽操作
imgS = Image.open('./car.jpg').convert('RGB').convert('L')
imgUByte=img_as_float(imgS)
img =color.rgb2gray(np.array(imgUByte))
auto =openclose.closing(img, disk(5))  #半径为5的圆形滤波器

plt.subplot(121)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(122)
plt.title('bi yun suan image')
plt.imshow(auto,plt.cm.gray)





#开运算
plt.figure(num=5,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('kai yun suan')

#这里选择 灰度拉伸变换的 图 基础上 做开运算
imgUByte=img_as_float(im4)
img =color.rgb2gray(np.array(imgUByte))
autoOpen =openclose.opening(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(121)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(122)
plt.title('kai yun suan image')
plt.imshow(autoOpen,plt.cm.gray)


#图像增强

plt.figure(num=6,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('hei mao-bai mao-er zhi hua')

#黑帽 原图像减去它的闭运算
imgS = Image.open('./car.jpg').convert('RGB').convert('L')
imgUByte=img_as_float(imgS)
img =color.rgb2gray(np.array(imgUByte))
auto =openclose.black_tophat(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(321)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(322)
plt.title('hei mao image')
plt.imshow(auto,plt.cm.gray)

#白帽 原图像减去它的开运算

#imgS = Image.open('./car.jpg').convert('RGB').convert('L')
imgUByte=img_as_float(im4)
img =color.rgb2gray(np.array(imgUByte))
autoBaiMao =openclose.white_tophat(img, disk(5))  #半径为5的圆形滤波器


plt.subplot(323)
plt.title('origin image')
plt.imshow(img,plt.cm.gray)

plt.subplot(324)
plt.title('bai mao image')
plt.imshow(autoBaiMao,plt.cm.gray)


#图像二值化
#展示二值化

#灰度拉伸后的图 减去 灰度拉伸开运算后的图 进行二值化

#bim = Image.fromarray(im4-autoOpen).convert('1') 

bim = Image.fromarray(autoBaiMao).convert('1')
plt.subplot(325)
plt.title('erzhihua')
plt.imshow(bim,plt.cm.gray)

#bim.save("erzhihua_img.jpg")


#边缘检测
#http://www.cnblogs.com/smallpi/p/4555854.html
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

def imconv(image_array,suanzi):
    '''计算卷积
        参数
        image_array 原灰度图像矩阵
        suanzi      算子
        返回
        原图像与算子卷积后的结果矩阵
    '''
    image = image_array.copy()     # 原图像矩阵的深拷贝
    
    dim1,dim2 = image.shape

    # 对每个元素与算子进行乘积再求和(忽略最外圈边框像素)
    for i in range(1,dim1-1):
        for j in range(1,dim2-1):
            image[i,j] = (image_array[(i-1):(i+2),(j-1):(j+2)]*suanzi).sum()
    
    # 由于卷积后灰度值不一定在0-255之间，统一化成0-255
    image = image*(255.0/image.max())

    # 返回结果矩阵
    return image


# x方向的Prewitt算子
suanzi_x = np.array([[-1, 0, 1],
                    [ -1, 0, 1],
                    [ -1, 0, 1]])

# y方向的Prewitt算子
suanzi_y = np.array([[-1,-1,-1],
                     [ 0, 0, 0],
                     [ 1, 1, 1]])

'''
我们 还是采用Canny算子 结合 高斯 来 解决我们的需求 
首先用高斯滤波器平滑预处理
前小节二值化后的车辆图像简单有效的车牌定位算法（附源码和详细解析），
消除部分噪声，然后使用梯度工具，
计算前一步骤作用后的图像简单有效的车牌定位算法（附源码和详细解析）、
简单有效的车牌定位算法（附源码和详细解析）方向的梯度
并用公式3.17得到幅值和方向角，
之后采用非极大值抑制(NMS)方法细化梯度幅值（另一种说法，模），
缩小方向角θ，最终使用双阈值法定位并提取出边缘。
'''


# 生成高斯算子的函数
def func(x,y,sigma=1):
    return 100*(1/(2*np.pi*sigma))*np.exp(-((x-2)**2+(y-2)**2)/(2.0*sigma**2))

# 生成标准差为5的5*5高斯算子
suanzi1 = np.fromfunction(func,(5,5),sigma=5)

# Laplace扩展算子
suanzi2 = np.array([[1, 1, 1],
                    [1,-8, 1],
                    [1, 1, 1]])


#bim 是 灰度拉伸 并 图像增强 并 二值化的 图像

# 转化成图像矩阵
image_array = np.array(bim)



# 利用生成的高斯算子与原图像进行卷积对图像进行平滑处理
image_blur = signal.convolve2d(image_array, suanzi1, mode="same")


# 得到x方向矩阵
image_x = imconv(image_array,suanzi_x)

# 得到y方向矩阵
image_y = imconv(image_array,suanzi_y)

# 得到梯度矩阵
image_xy = np.sqrt(image_x**2+image_y**2)



# 梯度矩阵统一到0-255
image_xy = (255.0/image_xy.max())*image_xy

# 对平滑后的图像进行边缘检测
image2 = signal.convolve2d(image_blur, suanzi2, mode="same")

# 结果转化到0-255
image2 = (image2/float(image2.max()))*255

# 将大于灰度平均值的灰度值变成255（白色），便于观察边缘
image2[image2>image2.mean()] = 255

# 显示图像
plt.subplot(1,2,1)
plt.imshow(image_array,cmap=plt.cm.gray)
plt.axis("off")
plt.subplot(1,2,2)
plt.imshow(image_xy,cmap=plt.cm.gray)
plt.axis("off")

plt.figure(num=8,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('cu ding wei')
# 先对 Canny算子的结果闭运算
'''
对已经提取边缘轮廓的车辆图像简单有效的车牌定位算法（附源码和详细解析）
作闭运算。首先取简单有效的车牌定位算法（附源码和详细解析）大小的矩形模核，
对图像简单有效的车牌定位算法（附源码和详细解析）作膨胀操作，填补孔洞，
连通车牌区域，然后再用同等大小的矩形核模腐蚀，消除孤立的小区域，
保留大块连通的区域，
最后获得处理后图像简单有效的车牌定位算法（附源码和详细解析）。
'''
bg1 =openclose.closing(image_xy, rectangle(5,19))
# 再开运算
'''
再对图像bg1作开运算。同样，
首先选取[5,19]大小的矩形核模，对图像bg1作腐蚀操作，
进一步消除非车牌区域的小块噪声区域，
然后再用等大核模膨胀，得到消除了大部分背景噪声的车牌图像bg2。
'''
bg2 =openclose.opening(bg1, rectangle(5,19))
'''
再对上一步获取的图像bg2作[11,5]大小的矩阵核模开运算。
具体操作与第二步类似。得到基本只有车牌区域的二值图bg3，初步定位出车牌。
'''
#再开运算
bg3 =openclose.opening(bg2, rectangle(11,5))
#开运算是先腐蚀后膨胀的过程，可以消除图像上细小的噪声，并平滑物体的边界
#闭运算是先膨胀后腐蚀的过程，可以填充物体内细小的空洞，并平滑物体边界
plt.subplot(1,2,1)
plt.title('bg3')
plt.imshow(bg3,cmap=plt.cm.gray)
plt.axis("off")
#消除细小对象
bg4 =openclose.opening(bg3, rectangle(11,5))
bg5 =openclose.opening(bg4, rectangle(11,5))
bg6 =openclose.opening(bg5, rectangle(11,5))
bg7 =openclose.opening(bg6, rectangle(11,5))
plt.subplot(1,2,2)
plt.title('bg7')
plt.imshow(bg4,cmap=plt.cm.gray)
plt.axis("off")



auto =  im4 - bg7

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



#蓝色像素统计、行列扫描的车牌精确定位算法

plt.figure(num=10,figsize=(12,8),dpi=96) #设置窗口大小
plt.suptitle('biao zhun zheng tai')
print('标准正态分布')

# example data  
mu = 100 # mean of distribution  
sigma = 15 # standard deviation of distribution  
x = mu + sigma * np.random.randn(10000)  
      
num_bins = 50  
# the histogram of the data  
plt.subplot(211)
n, bins, patches = plt.hist(x, num_bins, normed=1, facecolor='blue', alpha=0.5)  
# add a 'best fit' line  
y = mlab.normpdf(bins, mu, sigma)  
plt.plot(bins, y, 'r--')  
plt.xlabel('Smarts')  
plt.ylabel('Probability')  
plt.title(r'Histogram of IQ: $\mu=100$, $\sigma=15$') 

# 二维正态分布
print('二维正态分布')
sampleNo = 1000;
mu = np.array([[1, 5]])
Sigma = np.array([[1, 0.5], [1.5, 3]])
R = cholesky(Sigma)
s = np.dot(np.random.randn(sampleNo, 2), R) + mu
plt.subplot(212)
# 注意绘制的是散点图，而不是直方图
plt.plot(s[:,0],s[:,1],'+')

plt.show()
