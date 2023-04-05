# Processor 会做些什么

## Processor* init_processor(intlength, intheight)

处理器会被初始化，使用传入的长和高。原点为左上角，从左到右为长，从上到下为高。

## void destroy_processor(Processor* self);

进程结束，销毁。

## Object *place_object(Processor *self, Object *object, int x, int y, int length, int height);

外部将Object对象初始化后（外部不需要初始化“block”和“host”字段），传入对象指针，并指定对象长高与左上角位置。

此后外部不应再访问传入的object指针。

## void step(Processor* self);

处理器进行“一步”的处理，具体包括以下步骤：

1. 扫描整个区域，获得所有存活的对象。
2. 检查哪些对象是第一次被添加到处理器里面的，处理器将调用它们的birth方法。
3. 调用上一轮死亡的对象的death方法。然后将其销毁
4. 调用所有对象的action方法。（如果对象正在被冰冻则不会调用）

   > 这里需要注意一点，对象是通过调用处理器提供的API来与其他对象交互的，对象无法互相直接操控。如果一个对象要交互另一个对象，它只能利用处理器API发出“请求”。而处理器在这个时候只是将它们的请求存储起来，并没有让交互生效。
   >
5. 结算状态
6. 使所有对象的交互请求生效。
7. 扫描整个区域，清除所有死亡的对象，注意，只是将其清理出区域，并没有销毁它们。因为在下一次step时将调用它们的death方法。

## ProcessorAnimeData export_anime_data(Processor* self);

导出本次step后要求动画引擎作画的动画数据。内容包含：

1. 玩家信息：即时生成
2. 静止特效
3. 运动特效

这些动画效果是怎样产生的呢？

1. 调用此方法时处理器会自动读取保存在处理器中的玩家信息
2. 对象调用处理器API，请求展示的动画信息

## 处理器API

以下是处理器提供给对象的可供调用的API：

### void (*request_move)(Processor *host, Object *source, int direction, int step);

### void (*request_teleport)(Processor *host, Object *source, int des_x, int des_y);

### void (*request_freeze)(Processor *host, Object *source, Object*target, intdegree)

### void (*request_burn)(Processor *host, Object *source, Object *target, int degree);

### void (*request_defend)(Processor *host, Object *source, Object *target, int degree);

### void (*request_weak)(Processor *host, Object *source, Object *target, int degree);

### void (*request_heal)(Processor *host, Object *source, Object *target, int heal);

### void (*request_hurt)(Processor *host, Object *source, Object *target, int damage);

所有机制的实现：

冰冻：一个Object被冰冻时，处理器将不会执行它的Action，每次step后冰冻degree减一，减到0时冰冻解除。此外处理器将自动为冰冻物体附加冰冻效果。

烧伤：一个Object被烧伤时，处理器将每step扣除其BURN_HP血量，每次step后烧伤degree减一，减到0时烧伤解除。此外处理器将自动为烧伤物体附加烧伤效果。此外冰冻和烧伤效果，后面被附加上的会挤掉前面的

防御：当Object被处于defend状态时，其受到hurt被减去degree。处理器自动附加动画效果

虚弱：当Object被处于weak状态时，其造成hurt被减去degree。处理器自动附加动画效果

治疗和伤害：顾名思义。

移动和瞬移：移动只能直线移动，而且不能有障碍物阻挡，瞬移无视路径上的障碍物。
