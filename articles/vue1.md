---
title: Vue学习笔记（一）
date: 2017-05-24 22:25:32
tags:
---
# 本系列之缘起

前段时间决定做一件事：每天写一个实例，积少成多就是一个项目。从今天开始实践。

选定的实践目标为 ： 学会Vue，并构建中型项目。

这是本系列的第一篇。我不能保证会有第50篇。但是10篇总是会有的。

# 配置Vue开发环境

首先安装Vue。

```
$ sudo npm install vue-cli -g
```

如果觉得每次输入sudo浪费时间，可以给全局的node模块提权：

```
$ sudo chmod -R 777 /usr/local/lib/node_modules/
```

安装完成之后，就可以用vue-cli创建Vue应用了。创建完成后使用npm run dev启动。

```
$ vue init webpack project-name

$ cd project-name
$ npm install
$ npm run dev

```
之后访问浏览器的http://localhost:8080 可以看到Vue的欢迎界面，说明环境配置成功。

# 完成第一个组件的编写

观察src目录

![src目录](/images/src.png)

可以发现vue生成的文件，components下有Hello.vue,我们可以依样画葫芦，写一个Me.vue
内容基本是复制粘贴，最终修改如下

```

<template>
<div class="me">
    <h1>{{msg}}</h1>
</div>
</template>

<script>
export default {
  name: 'me',
  data () {
    return {
      msg: 'Hello World'
    }
  }
}
</script>

```

接下来有两种选择可以把我们刚写的Me.vue显示出来。

*  1.配置到router目录下的index.js中，只需要引入Me.vue，并在routes中添加一个Me组件即可。此时
访问http://localhost:8080/#/Me 即可看到新加的页面。

index.js中新加的内容如下
```
import Me from '@/components/Me' //add
export default new Router({
  routes: [
    {
      path: '/',
      name: 'Hello',
      component: Hello
    },
    {//add
      path: '/Me',
      name: 'My',
      component: Me
    }
  ]
})
```
* 2.把Me.vue添加到Hello.vue中
修改Hello.vue的script中内容如下：

```
import Me from '@/components/Me.vue'
export default {
  name: 'hello',
  data () {
    return {
      msg: 'Welcome to Your Vue.js App'
    }
  },
  components: { Me }
}
```
总的来说就是引入Me.vue，并添加一个字段components，内容为Me。
完成之后的效果如下：
![展示](/images/show.png)

至此，完成了新加一个component的任务。

# 加载数据

先说个题外话，eslint太烦人了，检查太严格，连多了个空格都要报错，对于我这种需要快速写代码检验效果的人简直是折磨，
果断禁掉。我承认eslint有好处，但是这里为了快速写代码，必须禁掉。
方法：
在eslintignore中添加src/*,这样src下任何文件都不会被eslint检查。
如果是团队里写代码，最好还是把eslint打开，这样保证团队代码风格尽量一致。

之后我们可以加载数据了。

```
npm install vue-resource --save
```

在Me.vue的data下面添加

```
mounted: function() {
    this.$http.jsonp('', {}, {
        headers: {

        },
        emulateJSON: true
    }).then(function(response) {
    }, function(response) {
    });
  }
```

这样即可异步加载外部网站的数据。

