# aws_iot_test
the aws iot sdk test , build for ARM

########################################################################################
# note 3
########################################################################################
# AWS iot:
sdkTest/sub

xk_Policy
{
	"Version": "2012-10-17",
		"Statement": [
		{
			"VersionEffect": "Allow",
			"Action": "iot:*",
			"Resource": "*"
		}
	]
}


# ç»植:
我们可以从sdk源码中提取出我们需要的部分组成我们实际使用的代码
(1)新建文件夹aws_iot_test
(2)将aws-iot-device-sdk-embedded-C 中 certs external_libs include platform src 这5个文件夹复制到该文件夹下
(3)将aws-iot-device-sdk-embedded-C/samples/linux/subscribe_publish_sample 中文件复制到该文件夹下
(4)修改Makefile
修改APP_NAME 为自己应用名，如aws_iot_test
修改IOT_CLIENT_DIR 为 .
(5)修改主程序文件名
将subscribe_publish_sample.c文件名改为 自己应用名.c
mv subscribe_publish_sample.c aws_iot_test.c
(6)修改主程序中certs 文件路径
aws_iot_test.c中44行 char certDirectory[PATH_MAX + 1] = “../../../certs”;为 ./certs
(7)make 运行测试 aws_iot_test 和1.5中结果一致说明，说明当前代码可用

交叉编译到嵌入式linux平台
到/external_libs/mbedTLS目录下 ，执行交叉编译
cd /external_libs/mbedTLS
make clean
make CC=arm-linux-uclibcgnueabi-gcc

交叉编译测试程序
修改Makefile
将CC=gcc 替换为
CC=arm-linux-uclibcgnueabi-gcc
回到程序根目录执行make

之后移植到项目的/system/中，并加入编译
inhand/configs/VG9-VG9system.configs中增加：+CONFIG_AWS_IOT_TEST=y
rules/Aall.mk    +includelude rules/aws_iot_test.mk
rules/configs.mk    +obj-$(CONFIG_AWS_IOT_TESTEST) += aws_iot_test
添加 rules/aws_iot_test.mk

将测试程序和CONFIG_AWS_IOT_TESTESTerts文件夹放到目标机同一目录下运行!
在aws_iot_test.mk­用 cp 实现


