## **项目4：基于MDK完成第三方TencentOS Tiny pack和软件包封装，可以使用MDK pack直接生成适合不同MCU的TencentOS Tiny工程**



## 一、安装软件包

![image-20210904160537403](C:/Users/12692/AppData/Roaming/Typora/typora-user-images/image-20210904160537403.png)



1、安装包会自动识别我们的Keil的软件包存放目录

![image-20210904160824233](https://i.loli.net/2021/09/04/Au4wDyfWnPKYV5R.png)



2、同意相关协议

![image-20210904160859008](https://i.loli.net/2021/09/04/zhIn6Dps5M4vf7E.png)



3、等待安装完成

![image-20210904160946819](https://i.loli.net/2021/09/04/BQTMGuzr87KPalI.png)



## 二、新建工程文件

1、选择新建工程路径，填写工程名称

![image-20210904161348068](https://i.loli.net/2021/09/04/f3ha5lWgkQVmFOT.png)



2、选择处理器种类

此处可以选择CM3处理器

![image-20210905102835493](https://i.loli.net/2021/09/05/1ysjDafdKZ6XNC3.png)

![image-20210905102934306](https://i.loli.net/2021/09/05/jMBIqQvy6OrCGVU.png)



如上，如果我们下了ST的软件包就可以直接使用相关芯片

此处以STM32F429IGTx为例

![image-20210904161620444](https://i.loli.net/2021/09/04/K5SH7fC9vqesmPb.png)



3、勾选TencentOS tiny软件包，并进行Resolve添加条件依赖

![image-20210904161721723](https://i.loli.net/2021/09/04/7QTcVwbzuyBgloA.png)



如果出现以下问题，说明CMSIS:CORE冲突了（软件包1.6.0版本解决了这个冲突）

![image-20210904161910247](https://i.loli.net/2021/09/04/RIgmN3v1PLW5jhO.png)



解决方法：直接勾选CMSIS==>CORE

勾选任意一个CORE即可，此处勾选了5.5.0版本的CORE

![image-20210904162007516](https://i.loli.net/2021/09/04/ocfBV9nztsRl1w6.png)



点击 OK 后，可以看到侧栏Project情况

可见软件包自动添加f429的启动文件

![image-20210904162336044](https://i.loli.net/2021/09/04/Hyt25JaMVhkA8PS.png)



接口文件会对应相关core，例子中F429为armv7m cm4

![image-20210904212617096](https://i.loli.net/2021/09/04/k6TNH3VvBpLArI9.png)



## 三、修改tos_config.h

此文件可以对TencentOS Tiny进行任意剪裁

![image-20210904162540064](https://i.loli.net/2021/09/04/irdf6P3TxpFDujE.png)

其中

`#include "RTE_Components.h"
#include  CMSIS_device_header `

用于自动识别芯片头文件，用户不用修改

### Run-Time-Environment组件文件由软件包识别相关芯片自动生成

![image-20210904163016015](https://i.loli.net/2021/09/04/SMgIda8CJKthu6Z.png)



## 四、添加用户模板文件

右键相关文件夹 ==> Add New Item ==> User Code Template 

![image-20210904163416495](https://i.loli.net/2021/09/04/bUuxkm6lq1Da5O3.png)



如果遇到如下警告

![image-20210904163756890](https://i.loli.net/2021/09/04/EqA9RQ8lwSF7UGu.png)

解决方法：

①选项 ==> Target ==> ARM Compiler 中选择Use default compiler version 5

![image-20210904163848437](https://i.loli.net/2021/09/04/pWBxeCi2LQ5gFoI.png)

②选项 ==> C/ C++中勾选C99 Mode

![image-20210904212008267](https://i.loli.net/2021/09/04/QDx154bYPViB3fU.png)



main.c用户模板中

CMSIS-RTOS 'main' function template部分使用的是CMSIS-RTOS通用API

![image-20210904214618813](https://i.loli.net/2021/09/04/rmQOdjRLeoB8zPZ.png)



TencentOS tiny 'main' function template部分使用的是TencentOS tiny的API（已注释掉）

![image-20210904214803075](https://i.loli.net/2021/09/04/DEQOrJW4NleyUPR.png)



编译一下有无报错

![image-20210904214850667](https://i.loli.net/2021/09/04/dJuLA6SWsgDkzv1.png)

## 五、添加库文件

此处HAL库为例

如果我们下好了ST提供的HAL软件包可以在包管理中勾选相关内容

![image-20210904220727848](https://i.loli.net/2021/09/04/LO9r3xZ5gjqe4JA.png)

（如果缺少某些组件会提示我们用CubeMX生成）

![image-20210904220925580](https://i.loli.net/2021/09/04/WtydN1isuLYlwzS.png)



或者直接手动添加相关库文件（较麻烦）

![image-20210904223645070](https://i.loli.net/2021/09/04/fw9nLF6xQ4c2yvD.png)

添加库头文件

![image-20210904223846731](https://i.loli.net/2021/09/04/XrxmhoBOCEqzH2U.png)



## 六、添加用户文件

同上，根据底板硬件，将我们需要的文件添加到工程中

修改一下模板文件main.c，然后编译下载到MCU上

![image-20210905102208354](https://i.loli.net/2021/09/05/bnlfEvdPwk9zXBa.png)



串口可打印字符串

![image-20210905100918302](https://i.loli.net/2021/09/05/cR1N9VkCzKsQUut.png)



## 七、补充

1、可以看到.pdsc文件的RTX配置，使用了.lib管理整个kernel，简化了pdsc。不过后来放弃了这种做法，因为在工程文件中会看不到源代码

2、目前覆盖cm0、cm3、cm4、cm7



## Generate CMSIS Pack for Release

This folder contains TencentOS Tiny software components (RTOS)

To build a complete CMSIS pack for installation the following additional tools are required:

 - **PACK.xsd**     (PDSC detector)

 - **PackChk.exe**     (Packing tool detector)
 - **7z.exe (7-Zip)** Version: 16.02 (File Archiver)

Using these tools, you can generate on a Windows PC:

 - **CMSIS Software Pack** using the batch file **gen_pack.bat** (located in ./TencentOS-tiny-softpack).



## Directory Structure

| Directory                                   | Content                                                      |
| :------------------------------------------ | :----------------------------------------------------------- |
| CMSIS/Core                                  | CMSIS-Core(M) related files (for release)                    |
| CMSIS/CoreValidation                        | Validation for Core(M) and Core(A) (NOT part of release)     |
| CMSIS/DAP                                   | CMSIS-DAP related files and examples                         |
| CMSIS/Driver                                | CMSIS-Driver API headers and template files                  |
| CMSIS/DSP                                   | CMSIS-DSP related files                                      |
| CMSIS/RTOS                                  | RTOS v1 related files (for Cortex-M)                         |
| CMSIS/RTOS2                                 | RTOS v2 related files (for Cortex-M & Armv8-M)               |
| CMSIS/Pack                                  | CMSIS-Pack examples and tutorials                            |
| CMSIS/DoxyGen                               | Source of the documentation                                  |
| CMSIS/Utilities                             | Utility programs                                             |
| CMSIS/RTOS/TencentOS_tiny/INC               | Store TencentOS_tiny to cmsis_os API header file             |
| CMSIS/RTOS/TencentOS_tiny/LIB               | Store TencentOS_tiny CPU architecture                        |
| CMSIS/RTOS/TencentOS_tiny/SRC               | Store TencentOS_tiny kernel，TOS_CONFIG，files related to compilation |
| CMSIS/RTOS/TencentOS_tiny/UserCodeTemplates | Store TencentOS_tiny User code templates                     |
| Docs                                        | Store project description documents                          |



