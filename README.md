# SmartCar
The 16th National Intelligent Car Competition for College Students in 2021
第十六届全国大学生智能车竞赛双车接力组华南赛区三等奖（翻车组）。
  直立车（改过三次结构，最后一次的结构还算比较满意）
  姿态检测用的是ICM20602+互补滤波
  控制用的是速度环增量式（外环）、角度环位置式（内环）、角速度串级pid，个人感觉比并级更稳点，但也更难调出好的参数
  
  第一次结构：机械零点最好的一次，但是考虑到能不能上坡道的问题，只能放弃
  ![IMG20210311215659](https://user-images.githubusercontent.com/85218852/161699850-848422bd-d4aa-4ee3-976e-eb1efaddf48c.jpg)

  
  第二次结构：没考虑到传球之前的结构，跑的时候“屁股”太低，不方便接球
  ![IMG20210411190114](https://user-images.githubusercontent.com/85218852/161699823-818f3f92-b663-4a52-ac92-55e03c468292.jpg)

  第三次结构：把传球考虑进来后，同时把重心调低了
  ![IMG20210720161828](https://user-images.githubusercontent.com/85218852/161699879-d0419d1c-2899-4e38-84f7-a6ee7f7eb022.jpg)

  
  三轮（改过三次，但是感觉越改越烂，重心越改越往前）
  原本改之前在锐角弯后轮弯时不会飘的，改之后就会飘了
  用了模糊控制来控制弯道曲率和速度的关系，直道加速，弯道减速
  
  第一次结构：电池放在中间，重心偏前
  ![IMG20210523222707](https://user-images.githubusercontent.com/85218852/161700941-3cf64cd5-29d7-45cf-b880-8fd753eb8032.jpg)
  
  第二次结构：电池放到后面
  ![IMG20210531211502](https://user-images.githubusercontent.com/85218852/161700988-8d303f8f-9453-494e-9a1f-7b4569fedc3e.jpg)
  省赛尝试了摄像头，效果还没纯电磁好
  ![IMG20210707233853](https://user-images.githubusercontent.com/85218852/161701176-b5f141a2-687d-4acf-b1fa-88142be683b0.jpg)
  
  第三次结构：不忍直视，搞成装甲车一样，重心混乱
  ![IMG20210712030947](https://user-images.githubusercontent.com/85218852/161701041-526c3002-eb67-4708-ad0c-3cad183fd4b2.jpg)

  
  传球用的是磁铁+魔术贴，三轮传球，撞上直立车后，直立车检测到位移就开始，同时给三轮发标志位，三轮停车。这种传球方法速度很快，直接撞上去，而且魔术贴粘性比磁铁强，怎么撞最后都会粘在魔术贴上。
  ![IMG20210610195209](https://user-images.githubusercontent.com/85218852/161701251-28a547d0-bb5c-408f-8dc9-2f6582961c30.jpg)

  芯片用的是mm32spin27ps，ram才12k，尝试过摄像头，带不动，最后放弃
