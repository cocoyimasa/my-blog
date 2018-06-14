---
title: UI框架项目重启
date: 2017-06-10 22:54:41
tags:
---
UI框架项目重启。

下午的时候搭起了骨架。骨架基本思路是微型React，或者说是只要有个组件化模型就行。

我本来也没准备依赖任何库或者框架，所以基本代码是从零写起。本来想用个模块化库，看了看seajs实在没有想用的冲动，作罢。还是不想添加任何依赖，大不了以后代码全重构成ES6。

反正现在就这破样子，代码写的不是很好，但是也不想花精力重构。重构是个时间杀手，尤其对于独立开发者而言，重构是个无底洞，会严重拖慢代码节奏，打乱思路。这点在我之前写编译器时深有体会。我是个普通人，一步到位很难做到，当时却一心想要优化，无形中浪费了很多时间，亲身实践了“过早优化是万恶之源”，这句话也算是个真理。

因为实在懒得记CSS样式具体的条款，所以也是一边写一边查，也不觉得效率低多少，反而轻车上路十分舒适。

JS这门语言的动态性经常是会被忘记的，写习惯了C++、C#，转过来颇有些不适应。没找个C#工作也是遗憾，不过也知道C#工作也未必看得上我这微末的技能。现在这些面试，大多根本面不出面试者水平，平日里不写代码的人，各个找的工作比我强百倍，令我惊愕，却也释然，咱这表达能力不行，外表也容易被人轻视，难怪。我不太能感觉到一丝尊严，尤其是面试中被面试官各种鄙视令我十分不舒服。本是同行，相煎何太急啊。明明都是查文档就能搞定的事，非要认为是能力问题？如果是我反过来面试他们呢？他们能保证不错？我觉得我一样可以问的对方哑口无言。术业有专攻，何必因为一方面失误否定一个人？我曾经的代码热情随着嘈杂的社会环境和蹉跎的生活也被消磨的差不多了。混成这样也是惨，生活越发觉得枯燥和单调，无聊到天天自言自语。说不定日后会改行。

贴一小段今天的成果：
```javascript
window.onload=ui;
    function ui(){
        var ui = UI();
        function UI(){
            /*{Control: ,tagName:div,attrs:{},children}*/
            function createClass(jsonObject,children){ /*just for extension*/
                var el = document.createElement(jsonObject.tagName);
                for(var attr in jsonObject.attrs){
                    el.setAttibute(attr,jsonObject[attr]);
                }
                if(children){
                    el.appendChild(children);
                }
            }
            function render(el,root){
                root.appendChild(el.renderDOM());
            }
            function getFunctionNameString(funcStr){
                var reg = /function\s*([a-zA-Z_$]*)/;
                var matches = reg.exec(funcStr);
                return matches[1];
            }
            function inherit(child,parent){
                var parentObj = eval('new '+getFunctionNameString(parent.toString())+'()');
                child.prototype = parentObj;
                child.prototype.constructor = child;
            }
            return {
                createClass:createClass,
                render:render,
                inherit:inherit
            };
        }
        /*utils start*/
        function childrenStringGenerate(tagName,className,propValues){
            var children = "";
            for(var i in propValues){
                children += '<'+tagName+' class="'+className+'">'+
                propValues[i]+'</'+tagName+'>';
            }
            return children;
        }
        /*utils end*/
        function UIControl(props){
            this.el = null;
            this.state = {}; 
        }
        UIControl.prototype.init = function init(){//用来设置state

        }
        UIControl.prototype.setState = function setState(state){//不允许子类覆盖
            for(var st in state){
                if(state.hasOwnProperty(st)){
                    this.state[st] = state[st];
                }
            }
            var preEl = this.el;
            this.el = this.renderDOM();
            if(this.onStateChange){
                this.onStateChange(preEl,this.el);//更新控件
            }
        }
        UIControl.prototype.createDOMFromString = function createDOMFromString(htmlString){
            var div = document.createElement('div');
            div.innerHTML = htmlString;
            return div;
        }
        UIControl.prototype.renderDOM = function(){
            this.el = this.createDOMFromString(this.render());
            return this.el;
        }

        function UIMenu(){
            this.style = {
                menu:'ui-menu',
                menuItem:'ui-menu-item',
                clearFix:'ui-clear-fix'
            };
        }
        ui.inherit(UIMenu,UIControl);
        //[] => String
        UIMenu.prototype.setChildren = function setChildren(children){
            this.children = "";
            for(var i in children){//注意for..in i是index 需要使用children[i]
                this.children += '<li class="'+this.style['menuItem']+'">'+
                children[i].render()+'</li>';
            }
        }
        //{} => Void
        UIMenu.prototype.setCSS = function setCSS(cssObj){
            for(var key in cssObj){
                this.style[key] = cssObj[key];
            }
        }
        //Void => String
        UIMenu.prototype.render = function render(){
            return '<a><ul class="'+this.style['menu']+'">'+
            this.children+
            '<div class="'+this.style['clearFix']+'"></div>'+
            '</ul></a>';
        }
        function UIMenuItem(props){
            this.props = props;
            this.render = function(){
                return "<button>"+this.props.value+"</button>";
            }
        }
        ui.inherit(UIMenuItem,UIControl);

        function UIMenuItemSelectOption(props){
            this.props = props;
            this.render = function(){
                var options = childrenStringGenerate('option','',this.prop.value);
                return '<select>'+options+'</select>';
            }
        }
        function UIDropdown(props){
            this.props = props;
            this.style = {
                dropdownContainer:'ui-dropdown-container',
                dropdown:'ui-dropdown',
                dropdownList:'ui-dropdown-list',
                dropdownItem:'ui-dropdown-item'
            }
            setTimeout(this.onClick.bind(this),0);
        }
        ui.inherit(UIDropdown,UIControl);
        UIDropdown.prototype.onClick = function(){
            var dropdownControl = document.getElementsByClassName(this.style['dropdown'])[0];
            var that = this;//
            dropdownControl.addEventListener('click',function(event){
                var items = document.getElementsByClassName(that.style['dropdownList'])[0];
                if(items.style.display == 'none'){
                    items.style.display = 'block';
                }
                else{
                    items.style.display = 'none';
                }
            },false);
            
        }
        UIDropdown.prototype.render = function(){
            var children = childrenStringGenerate('div',this.style['dropdownItem'],this.prop.value);
            return '<div class="'+this.style['dropdownContainer']+'"><div class="'+this.style['dropdown']+'"></div>'+
            '<div class="'+this.style['dropdownList']+'">'+children+
            '</div>'+
            '</div>';
        }
        
        function UIScroll(props){
            this.style = {
                scroll:'ui-scroll',
                scrollItem:'ui-scroll-item'
            }
            this.props = props;
        }
        UIScroll.prototype.render = function(){
            var children = childrenStringGenerate('img',this.style['scrollItem'],this.prop.value);
            return '<div class="'+this.style['scroll']+'">'+children+'</div>';
        }

        var menu = new UIMenu();
        menu.setChildren([
            new UIMenuItem({value:"Test1"}),
            new UIMenuItemSelectOption({value:["Test1 Test1 Test1","Test2"]}),
            new UIDropdown({value:["Test1 Test1 Test1","Test2"]})
        ]);
        ui.render(menu,document.getElementById('root'));
    }
```
