说明
==========
该模块用于对外提供数据接口

使用方法
==========
1.启用模块
2.在“admin/config/system/odr_remote”配置keys，需要注意：
	2.1 不要删除已存在的keys.
	2.2 如果是要创建新的数据接口，请生成1个新key，然后拿到其项目中使用
	2.3 Key的使用方法:
			参考hook_menu中的odr_remote/request/%/%
			第一个% => key
			第二个% => type(数据接口type)
			
