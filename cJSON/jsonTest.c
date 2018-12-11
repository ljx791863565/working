#include <stdio.h>
#include <cJSON.h>
#include <stdlib.h>

//构建json
/*
 * 假设要构建的json
 * "semantic":{
 *		"slots":{
 *			"name" : "张三"
 *		}
 * },
 * "rc" : 0,
 * "openation0" : "CALL",
 * "service" : "telephone",
 * "text" : "打电话给张三"
 * }
 */
void create_json(void)
{	
	cJSON *root = cJSON_CreateObject();
	cJSON *item = cJSON_CreateObject();
	cJSON *next = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "rc", cJSON_CreateNumber(0));	//跟节点下添加
	cJSON_AddItemToObject(root, "openation", cJSON_CreateString("CALL"));
	cJSON_AddItemToObject(root, "service", cJSON_CreateString("telephone"));
	cJSON_AddItemToObject(root, "text", cJSON_CreateString("打电话给张三"));

	cJSON_AddItemToObject(root, "semantic", item);	//在root节点下添加item节点
	cJSON_AddItemToObject(item, "slots", next);		//在semantic节点下添加next节点
	cJSON_AddItemToObject(next, "name", cJSON_CreateString("张三"));

	printf("%s\n", cJSON_Print(root));

	return;

}

//以递归方式打印json内层键值对
void printJson(cJSON *root)
{
	for (int i = 0; i < cJSON_GetArraySize(root); i++){
		cJSON *item = cJSON_GetArrayItem(root, i);
		//如果对应的键值仍为cJSON_Object,递归调用printJson
		if (cJSON_Object == item->type){
			printJson(item);
		//否则打印
		}else{
			printf("%s->", item->string);
			printf("%s\n", cJSON_Print(item));
		}
	}
}
int main()
{
	char *jsonStr = "{\"semantic\":{\"slots\":{\"name\":\"张三\"}},\"rc\":0, \"operation\":\"Call\", \"service\":\"telephone\", \"test\":\"打电话给张三\"}";
	cJSON *root = NULL;
	cJSON *item = NULL;

	root = cJSON_Parse(jsonStr);
	if (!root){
		printf("Error before :[%s]\n", cJSON_GetErrorPtr());
	}else {
		printf("%s\n", "有格式打印json");
		printf("%s\n\n", cJSON_Print(root));
		printf("%s\n", "无格式打印json");
		printf("%s\n\n", cJSON_PrintUnformatted(root));

		printf("%s\n", "一步步获取name健值对:");
		
		printf("%s\n", "获取semantic下的cjson对象");
		item = cJSON_GetObjectItem(root, "semantic");
		printf("%s\n", cJSON_Print(item));

		printf("%s\n", "获取slots下的cjson对象");
		item = cJSON_GetObjectItem(item, "slots");
		printf("%s\n", cJSON_Print(item));

		printf("%s\n", "获取name下的cjson对象");
		item = cJSON_GetObjectItem(item, "name");
		printf("%s\n", cJSON_Print(item));

		printf("%s:", item->string);
		printf("%s\n", item->valuestring);

		printf("\n%s\n", "打印json所有内层键值对");
		printJson(root);

		printf("create json\n");
		create_json();
	}
	return 0;
}
