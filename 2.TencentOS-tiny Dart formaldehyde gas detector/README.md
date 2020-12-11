# TencentOS tiny dart-sensor detector 

#### 介绍
基于腾讯物联网操作系统的英国达特甲醛探测仪

#### 软件架构
![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXV3NjYnExaWIzMkJpY0NmcjV1Z2xVZnlwVFZZdmZ6bDlueUlOeWx0UDdPbFdMR2liQWhTa3plVWp3LzY0MA?x-oss-process=image/format,png)

#### 使用说明

项目图片展示效果：**(Powe by TencentOS tiny)**

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXU2lhY1BJcmJ3OXFzcjhQWXlHRHdpYnhkMUQ3MXc1UVFqaE1jR0RpYUF3ZTY1bHFCRVAzczZpYlpKZy82NDA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXZEdVU3RBbWNpYWNCTVZmRXB4UW1icDZ3ZGlhT1Rqd1BPN0R0VHlhUkZnNzF0RGxRZko0Sm0xUVEvNjQw?x-oss-process=image/format,png)

项目开源仓库，在两个地方存储，分别是个人还有腾讯开源的公共仓

- 个人`TencentOS tiny dart-sensor detector`

```go
https://gitee.com/morixinguan/tencent-os-tiny-dart-sensor-detector.git
```

- 腾讯开源仓`TencentOS tiny dart-sensor detector`

```go
https://gitee.com/Tencent/TencentOS-Tiny-IoT-Projects.git
```

## 1、硬件平台(小熊派)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXbHFjTjU3NzF2YW1OTU5FZ2dER3Q5QUZ2YWliWXlFejFJNnZsejhsUnQ4blpCcW51eHd2YTVuUS82NDA?x-oss-process=image/format,png)

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSWliWjA0M3lGYU1lTVJHaktYSkRuZk8zdGFod1NMVHd0WmJBeWhuQlpSTzMzQllUZDVpY0p0bXpjeDB2TmlhQ2ljaWJlZG95a2libU54QTBnRVEvNjQw?x-oss-process=image/format,png)

## 2、支持的操作系统平台

目前仅支持`TencetOS tiny`，后续计划采用CMSIS-OS框架，将OS部分剥离出来，以达到任何一个OS均可适配本项目。

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXeVIxWWdpYmV0SmFPeXNmbThuOGx3eGFpY1R4NHduNmxlekNZWUNCenVaZlgwU05xeHJXZ0dkRHcvNjQw?x-oss-process=image/format,png)

##  3、整体软件框架图

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X2pwZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXT0FaQ0FJeU1FN1M2N3JmSHdEcmpIVmpnR3lhRG9pYkFXRlh5TGRpY2lhV2czRkRIaWN4T0ZBNzRlQS82NDA?x-oss-process=image/format,png)

### 核心软件框架图

![img](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9tbWJpei5xcGljLmNuL21tYml6X3BuZy9TWWljZUpLNzhDSTl2WUFpYm94alZjUTB1ZnlJNURabUdXaWN0SU5rNlZpYjJOUGlja2daSWpxemljaWFENXV0ek0welQzQjVFaWNkcE4xWnpwSEJxYkhPZFU0aWNyZy82NDA?x-oss-process=image/format,png)

## 4、功能说明

- 中文彩色液晶显示
- 灵敏度三档可调
- 密码权限管理功能
- 支持外部串口调试
- 可自由调整设置时间
- 曲线显示报警值(待完成)
- 支持无线数据上传(待完成)
- 高性能进口串口协议英国达特甲醛传感器
- 支持声光报警，可通过配置实现(待完成)
- 主页面显示各项技术指标和气体浓度值
- 具有数据存储及查询功能，可以存储数据1000条(待完成)

等等可拓展会在后续持续维护和加入。

## 5、软件版本

| 发布版本 | 描述                                         |
| :------- | :------------------------------------------- |
| [V1.0.0] | 初次发布，完成基本功能及相关功能和稳定性验证 |

## 6、问题反馈

欢迎提`Issues`的形式向我的个人仓以及腾讯开源仓提交问题和BUG报告，本项目会持续进行维护。

## 7、版权和许可

本项目遵循`Apache License v2.0`开源协议。鼓励代码共享和尊重原作者的著作权，可以自由的使用、修改源代码，也可以将修改后的代码作为开源或闭源软件发布。

6.  https://gitee.com/gitee-stars/)
