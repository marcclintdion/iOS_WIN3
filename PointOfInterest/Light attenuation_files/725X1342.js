// v:9.3.2
var skimwords_horizontal_distance = 80;
var skimwords_vertical_distance = 80;
var noskimwords = true;
var noskoupon = true;
var noskimproducts = true;
var skimwords_instant = true;
var skimlinks_domain = 'go2.wordpress.com';
var skimlink_legacy_support = true;
(function(){var sa,ta,ua,ca,j,s,va,wa,xa,da,J,v,i,Q,ea,ya,za,l,D,t,K,z,R,fa,m,E,F,w,Aa,p,ga,ha,Ba,ia,S,L,q,Ca,Da,ja,T,Ea,Fa,Ga,Ha,Ia,Ja,Ka,x,La,ka,Ma,Na,la,u,Oa,n,Pa,U,V,W,ma,M,Qa,N,X,A,Y,Z,G,$,r,O,Ra,Sa,Ta,na,aa,y,o,B,oa,ba,P,C,pa,H,I,qa,d,ra={}.hasOwnProperty;z=R=null;m={pag:"",phr:{},pub:"",slc:0,swc:0,jsl:0,jsf:"",guid:"",uc:"",t:1};fa=/http:/g;l=function(){var a;a=navigator.userAgent.toLowerCase();a=/(webkit)[ \/]([\w.]+)/.exec(a)||/(opera)(?:.*version)?[ \/]([\w.]+)/.exec(a)||/(msie) ([\w.]+)/.exec(a)||
0>a.indexOf("compatible")&&/(mozilla)(?:.*? rv:([\w.]+))?/.exec(a)||[];return{browser:a[1]||"",version:parseFloat(a[2])||0}}();ha=[];Aa=(new Date).getTime();w=[];ga=[];p=t=null;K=!1;E=[];D=[];F=[];$=G=Y=M=ma=A=r=null;V=[];ba=P=oa=C=N=Z=U=W=X=null;y="";B=o=0;pa=!1;d=this;H=d.location;I="";sa=["noskim","norewrite"];ta="*doubleclick.net,*mjxads.internet.com,*pgpartner.co.uk,*pgpartner.com,*pricegrabber.co.uk,*pricegrabber.com,*overture.com,*youtube.com".split(",");Qa=function(){return!0};Ba=function(a){var b;
b=document.createElement("a");b.href=a;return O(b.hostname)};ua=function(){var a,b,c,e,g,f,h,k,j,i,l,n,p,q,s,t,u,v,w,x,y;R=null!=(a=document.getElementsByTagName("html"))?a[0]:void 0;E=null!=(b=d.skimlinks_included_classes)?b:[];D=null!=(p=d.skimlinks_excluded_classes)?p:[];F=null!=(s=d.skimlinks_included_ids)?s:[];z=d.force_location?Ba(d.force_location):H.hostname;r=null!=(t=d.skimlinks_tracking)?t:!1;A=d.skimlinks_site||d.skimlinks_sitename||!1;ma=null!=(u=d.skimlinks_domain)?u:"go.redirectingat.com";
M=null!=(v=d.skimlinks_google)?v:!1;Y=null!=M?M:"skimout";G=null!=(w=d.skimlinks_target)?w:!1;$=null!=(x=d.sl_test)?x:!1;V=null!=(y=d.skimlinks_exclude)?y:[];X=null!=(c=d.skimlinks_noright)?c:!1;W=null!=(e=d.skimlinks_exrel)?e:!1;U=null!=(g=d.skimlinks_byrel)?g:!1;Z=null!=(f=d.skimlinks_blocked_tag)?f:!1;N=0;C=null!=(h=d.skimlinks_pub_id)?h:"";if(d.skimlink_legacy_support)d.skimlinks=function(){return!0},d.mugicPopWin=function(){return!0},d.mugicRightClick=function(){return!0};o=null!=(k=d.skimlinks_dnt)?
k:0;B=null!=(j=window.skimlinks_nocookie)?j:!1;oa=null!=(i=d.noimpressions)?i:!1;ba=null!=(l=d.noskimlinks||d.noskim)?l:!1;P=null!=(n=d.noskimwords||d.noskim)?n:!1;pa=null!=(q=d.skim_toolbar)?q:!1;if(d.document&&d.document.referrer)I=d.document.referrer;Ia(z)&&(P=ba=!0);r&&!/^[a-z0-9_\\|]+$/i.test(r)&&(r=!1);m.pag=d.force_location||H.href;m.pub=C;m.uc=r;"undefined"!==typeof assign_skimwords_globals&&null!==assign_skimwords_globals&&assign_skimwords_globals();D.push("noskimlinks");return!0};Ia=function(a){var b,
c,e,g;if(d.noskim_domains){g=d.noskim_domains;for(c=0,e=g.length;c<e;c++)if(b=g[c],-1!==a.toLowerCase().indexOf(b.toLowerCase()))return!0}return!1};O=function(){var a;a=/^www\./i;return function(b){return b.replace(a,"")}}();s=function(){return document.addEventListener?function(a,b,c){if(a&&(a.nodeName||a===d))return a.addEventListener(b,c,!1)}:function(a,b,c){if(a&&(a.nodeName||a===d))return a.attachEvent("on"+b,function(){return 7>l.version&&!window.event?(setTimeout(function(){return c.call(a,
window.event)},100),!0):c.call(a,window.event)})}}();(function(){return document.createElement("div").getElementsByClassName?function(a,b){return q(a,b)?a:a.getElementsByClassName(b)}:function(a,b){var c;c=da(b);return ea(a,c)}})();i=function(){var a,b;b=[function(){var b,e,g,d;g=[["%20","+"],["!","%21"],["'","%27"],["\\(","%28"],["\\)","%29"],["\\*","%2A"],["\\~","%7E"]];d=[];for(b=0,e=g.length;b<e;b++)a=g[b],d.push([RegExp(a[0],"g"),a[1]]);return d}()];return function(c){var e,d,c=encodeURIComponent(c);
for(e=0,d=b.length;e<d;e++)a=b[e],c=c.replace(a[0],a[1]);return c}}();Ga=function(){var a;a=/^\/\/|https?:\/\//i;return function(b,c){return a.test(b)&&(!c||!z||-1===c.indexOf(z))&&(!z||-1===z.indexOf("."+c))}}();j=function(a,b,c){var e;3<=arguments.length&&("undefined"!==typeof a.setAttribute?a.setAttribute(b,c):a[b]=c);e=a[b];null==e&&(e=a.getAttribute(b));return e};v=function(a,b,c){arguments[1]="data-"+b;return j.apply(this,arguments)};Sa=function(a,b){var c;c=a.innerText||a.textContent||a.nodeValue;
if(2<=arguments.length)a.innerText?a.innerText=b:a.textContent=b,c=b;return c};aa=function(){var a,b;if(String.prototype.trim)return function(a){return null===a?"":String.prototype.trim.call(a)};a=/^\s+/;b=/\s+$/;/\S/.test("\u00a0")&&(a=/^[\s\xA0]+/,b=/[\s\xA0]+$/);return function(c){return null===c?"":c.toString().replace(a,"").replace(b,"")}}();La=function(a){var b,c,e,d,f;if("object"===typeof a||a instanceof Array){d="";e=0;c=a instanceof Array;for(f in a)ra.call(a,f)&&(b=a[f],0<e&&(d+=","),c?
d+=x(b):(b=x(b),d+='"'+f+'":'+b),e++);return c?"["+d+"]":"{"+d+"}"}return"string"===typeof a?(b=a.replace(/"/g,'\\"',a),'"'+b+'"'):isNaN(a)?"null":a.toString()};x=function(){var a;return"undefined"!==typeof JSON&&null!==JSON&&JSON.stringify&&'["la"]'===JSON.stringify(["la"])?(a=JSON.stringify,function(b){return a(b)}):La}();Q=function(){var a,b;a=/[-[\]{}()*+?.,\\^$|#\s]/g;b=/\s+/g;return function(c){return c.replace(a,"\\$&").replace(b,"s+")}}();da=function(a){a=Q(a);return RegExp("\\b"+a+"\\b",
"i")};q=function(a,b){return a.className?da(b).test(a.className):!1};ea=function(a,b){var c,e,d,f,h;e=[];a.className&&b.test(a.className)&&e.push(a);h=a.childNodes;for(d=0,f=h.length;d<f;d++)c=h[d],e=e.concat(ea(c,b));return e};wa=function(a){return-1!==encodeURIComponent(a).indexOf("%C3%82%C2%A3")};za=function(a){a=a.innerHTML.slice(0,4);if("http"===a||"www."===a)a.innerHTML="<span style='display:none!important;'>&nbsp;</span>";return!0};Ja=function(a){for(var b,c,e,d,a=a.parentNode;a&&a!==R;){c=
a.id;for(e=0,d=E.length;e<d;e++)if(b=E[e],q(a,b))return!1;for(e=0,d=F.length;e<d;e++)if(b=F[e],c===b)return!1;for(c=0,e=D.length;c<e;c++)if(b=D[c],q(a,b))return!0;a=a.parentNode}return E.length||F.length?!0:!1};Ea=function(a,b,c){null==c&&(c=!1);for(b=RegExp("\\b(?:(?:"+Q(b)+")|(?:noskim))\\b","i");null!=a&&a!==R;){if(a.className&&b.test(a.className))return!0;a=c?null:a.parentNode}return!1};xa=function(a,b){var c,e,g,f;q(a,"skimwords-link")||q(a,"skimwords-unlinked")?(f=q(a,"skimwords-link")?j(a,
"data-skimwords-word"):"url",c=j(a,"data-skim-creative"),e=j(a,"data-skim-product"),g=d.skimlinks_domain||"go.redirectingat.com","undefined"!==typeof settings&&null!==settings&&(g=settings.sw_domain||g),b="//"+g+"/?id="+C+""+(r?"&xcust="+r:"")+"&xs=2&url="+i(b)+"&xguid="+y+"&xword="+(f?f:"")+"&xcreo="+(c?c:"")+"&xpid="+(e?e:"")+"&sref="+i(H)+"&pref="+i(I)+""+(o?"&dnt="+o:"")+""+(B?"&fdnt=1":"")):Ea(a,"noskimlinks")||(c=j(a,"data-skim-creative"),b="//"+ma+"/?id="+C+""+(A?"&site="+A:"")+""+($?"&test="+
$:"")+""+(r?"&xcust="+r:"")+"&xs=1&url="+i(b)+"&xguid="+y+"&xcreo="+(a&&null!=c?c:0)+"&sref="+i(H)+"&pref="+i(I)+""+(o?"&dnt="+o:"")+""+(B?"&fdnt=1":""));return b};ia=function(a){var b;if((b=a.target||a.srcElement)&&!b.href&&a.currentTarget)b=a.currentTarget;for(;b&&"A"!==b.nodeName;)b=b.parentNode;return b};u=function(a){var b;b=ia(a);Ma(b);if(d.vglnk&&q(b,"skimwords-link"))a&&a.stopPropagation?a.stopPropagation():(a=d.event,a.cancelBubble=!0);return!0};Ma=function(a){var b,c,e,d,f,h;f="msie"===
l.browser&&7>l.version?1E4:100;b=!1;c=M;if(a&&a.nodeName&&"IMG"===a.nodeName)a=a.parentNode;if(a){h=a.href;if("msie"===l.browser&&a.childNodes.length&&3===a.childNodes[0].nodeType)d=a.innerHTML;(e=v(a,"skimlinks-href"))?b=!0:(e=xa(a,h),v(a,"skimlinks-href",e));c&&Ta(h);v(a,"skimlinks-orig-link")||(v(a,"skimlinks-orig-link",h),b=!1);a.href=e;setTimeout(function(){a.href=v(a,"skimlinks-orig-link");if(d)a.innerHTML=d;return!0},f)}return b};Ha=function(a){var b,c,e;if(e=ga)for(b in e)if(ra.call(e,b)&&
(c=e[b],c===a))return!0;return!1};Ka=function(a){var b,c;if(!Z)return!1;b=null!=a?a.previousSibling:void 0;if(!b)return!1;a=("["+Z+"]").toLowerCase();c=Sa(b);c=c.toLowerCase();c=aa(c);b=c.lastIndexOf(a);return-1!==b&&b+a.length===c.length};T=function(a){return!a||U&&a===U||!Ca(a)};Ca=function(a){var b,c,e,d;t=null;if(!a)return!1;a=a.toLowerCase();if(t)return t[a];t={};b=W?[W]:[];b=b.concat(sa);for(c=0,e=b.length;c<e;c++)d=b[c],t[d.toLowerCase()]=!0;return t[a]};va=function(){var a,b,c,e;p={};A&&V.push(A);
e=V.concat(ta);for(b=0,c=e.length;b<c;b++)a=e[b],p[a]=a.length;return p};Fa=function(a){var b,c,e;null===p&&va();if(!a)return!1;for(b in p)if(ra.call(p,b))if(c=p[b],0===b.indexOf("*")){if(b=b.substr(1),c-=1,e=a.lastIndexOf(b),-1!==e&&e===a.length-c)return!0}else if(a===b)return!0;return!1};ja=function(a,b){return Ga(a,b)&&!Fa(b)};Ta=function(a){var b,c,e;b=d.pageTracker;e=d.urchinTracker;c="/"+Y+"/"+a;if(null!=b&&b._trackPageview)return b._trackPageview(c),!0;if(e)return e(c),!0;if(d._gaq)b=d._gaq,
b.push(["_trackEvent",Y,"click",a]);return!1};J=function(a){var b,c,e;c=i('},"pub"');b="//t.skimresources.com/api/track.php";e=[];o&&e.push("dnt="+o);B&&e.push("fdnt=1");e.push("data=");b+="?"+e.join("&");b+=i(x(m).replace(fa,""));null!=a&&a.length&&(a.join(i(",")),b=b.replace(c,""+a+c));return[b,b.length]};na=function(){var a,b,c,e,d,f,h;if(oa)return!1;d=(new Date).getTime()-Aa;e=[];b=8E3;"msie"===l.browser&&(b=2E3);m.slc=N;m.swc="undefined"!==typeof sw_handlers&&null!==sw_handlers?sw_handlers:0;
m.jsl=d;m.guid=y;m.pref=I;m.phr={};a=J();a=a[1];for(c=d=0,h=ha.length;d<h;c=++d)if(f=ha[c],f=x(f).replace(fa,""),c=i('"'+c+'":'+f),!("msie"===l.browser&&c.length>b)){f=a+c.length+3*e.length;if(f>b)a=J(e),e=a[0],L(e,!1,{async:!0}),e=[],m.t=0,a=J(),a=a[1];e.push(c)}b=J(e)[0];"msie"===l.browser&&7>l.version&&(b=b.substring(0,4095));L(b,!1,{async:!0});la(1);return!0};la=function(a){if(10>a)return w=Na(),setTimeout(function(){return la(a+1)},2E3*a)};Na=function(){var a,b,c,e,d,f,h;b={};e=[];c=[];for(d=
0,f=w.length;d<f;d++)a=w[d],a.parentNode?c.push(a):b[a.href]=1;h=S();for(d=0,f=h.length;d<f;d++)a=h[d],b[a.href]&&e.push(a);ca(e);return e.concat(c)};ka=function(a){var b,c;c=new Date;b=c+300;a=ia(a);a=i('{"pubcode":"'+C+'","referrer":"'+H+'","pref":"'+I+'","site":"'+A+'","url":"'+a.href+'","custom":"'+r+'","product":"1"}');for(L("//r.skimresources.com/api/?call=track"+(o?"&dnt="+o:"")+(B?"&fdnt=1":"")+"&data="+a);c<b;)c=new Date;return!0};L=function(a,b,c){var e;var d,g,f,h,k,j,i=this;null==c&&(c=
{});d=c.charset||null;j=c.target||null;e=null!=(g=c.async)?g:!0,c=e;g=null!=j&&j.document?j.document:document;f=g.getElementsByTagName("head")[0];k=g.createElement("script");h=!1;k.type="text/javascript";if(d)k.charset=d;k.onload=k.onreadystatechange=function(){var a;a=i.readyState;if(!h&&(!a||"complete"===a||"loaded"===a))if(k.onload=k.onreadystatechange=null,h=!0,b)return b.call(j)};k.async=!1!==c;k.src=a;f.appendChild(k);return k};S=function(a){var b,c,d,g,f;b=null;a&&(b=RegExp("\\b"+Q(a)+"\\b",
"i"));f=[];g=document.getElementsByTagName("a");for(c=0,d=g.length;c<d;c++){a=g[c];try{a.href&&(!b||a.className&&b.test(a.className))&&f.push(a)}catch(h){console.log("Malformed IE url")}}return f};ca=function(a){var b,c,d,g,f,h,k,i,m;c=E.length||F.length||D.length;g=[];for(i=0,m=a.length;i<m;i++)if(b=a[i],d=O(b.hostname),b.sl_hidden_domain&&(d=O(b.sl_hidden_domain)),k=aa(b.href),h=j(b,"rel"),f=j(b,"onclick"),(!c||!Ja(b))&&!Ka(b))if(Ha(d,b)){if(T(h)){G&&j(b,"target",G);if("msie"===l.browser){if(wa(k))continue;
za(b)}null!=f&&-1!==f.toString().indexOf("return false")?s(b,"mousedown",u):s(b,"click",u);Ra(b,!1);Da(b);g.push(b);X||s(b,"contextmenu",u);Qa(b)}}else ja(k,d)&&T(h)&&(G&&j(b,"target",G),s(b,"click",ka),X||s(b,"contextmenu",ka));return g};Da=function(a,b){var c,e,g,f;if(d.link_icon||0<a.getAttribute("data-skim-product")&&d.skimwords_product_icon){if(0<a.getElementsByTagName("img").length)return!0;if("msie"===l.browser&&8>l.version)a.style.display="inline-block";g=c="";null!=b&&(c=d.skimwords_icon_class||
"",g=d.skimwords_icon_link_class||"");f=j(a,"title").replace("'","&#39;");e=d.link_icon||d.skimwords_product_icon;c="<a href='"+j(a,"href")+"' title='"+f+"' style='border:0px;padding:0;margin:0' class='skimlinks-icon-link "+g+"' skimlinked='skimlinked' target='_blank'><img src='"+e+"' class='"+c+"' skimlinked='skimlinked' style='margin: 0px 0px -3px 2px !important; float:none !important;  border:0px; float:none !important; display:inline !important;' /></a>";e=document.createElement("div");e.innerHTML=
c;c=e.childNodes[0];s(c,"mousedown",u);a.appendChild(c)}return!0};Pa=function(){"undefined"!==typeof skimwords&&null!==skimwords&&!P?skimwords():na();return!0};ya=function(){var a,b,c,d,g,f,h,i;g=S();c=[];d={};for(h=0,i=g.length;h<i;h++)a=g[h],b=O(a.hostname),f=aa(a.href),a=j(a,"rel"),ja(f,b)&&T(a)&&b&&!d[b]&&(c.push(b),d[b]=!0);return c};qa=function(){var a;ua();ba?"undefined"!==typeof skimwords&&null!==skimwords&&!P?skimwords():na():(a=ya(),a=i('{"pubcode":"'+C+'","domains":'+x(a)+"}"),a="//r.skimresources.com/api/?callback=skimlinksApplyHandlers"+
(o?"&dnt="+o:"")+(B?"&fdnt=1":"")+(pa?"&call=toolbar":"")+"&data="+a,L(a));return!0};n=function(){if(K)return!1;K=!0;qa();return!0};Ra=function(a,b){var c,e;e=a.style.cssText;e+=" ";if(d.link_background)c=d.link_background,-1===c.indexOf("#")&&(c="#"+c),e+="background-color: "+c+" !important; ";if(null!=d.link_tooltip)a.title=d.link_tooltip;if(b){if(d.skimwords_color)c=d.skimwords_color,-1===c.indexOf("#")&&(c="#"+c),e+="color: "+c+" !important; ";d.skimwords_weight&&(e+="font-weight: "+d.skimwords_weight+
" !important; ");if(d.skimwords_decoration)c=d.skimwords_decoration,e="double"===c?e+"border-bottom: 1px double !important; ":e+("text-decoration: "+c+" !important; ");if(d.skimwords_style)c=d.skimwords_style,e+="text-style: "+c+"; ";if(d.skimwords_link_style)c=d.skimwords_link_style,e+=c+"; ";c=" "+a.className;if(d.skimwords_link_class)c+=" "+d.skimwords_link_class,a.className=c.substring(1);if(d.skimwords_title&&null===a.getAttribute("title"))a.title=d.skimwords_title;if(null===a.getAttribute("title"))a.title=
"Shopping link added by SkimWords"}a.style.cssText=e;return!0};Oa=function(){return function(){var a,b,c;b=function(){if(K)return!0;try{document.documentElement.doScroll("left")}catch(a){return setTimeout(b,50),!1}return n()};a=function(){return document.addEventListener?function(){document.removeEventListener("DOMContentLoaded",a,!1);n();return!0}:document.attachEvent?function(){document.detachEvent("onreadystatechange",a);n();return!0}:function(){n();return!0}}();if("complete"===document.readyState)setTimeout(n,
1);else if(document.addEventListener)document.addEventListener("DOMContentLoaded",a,!1),d.addEventListener("load",n,!1);else if(document.attachEvent){document.attachEvent("onreadystatechange",a);d.attachEvent("onload",n);c=!1;try{c=null===d.frameElement}catch(e){}document.documentElement.doScroll&&c&&b()}return!0}}();d.skimlinksApplyHandlers=function(a){var b,a=null!=a?a:{};null!=d.skimlinks_runner&&(d.skimlinks_runner.skimlinks=1);b=S();ga=a.merchant_domains;a.guid&&""===y&&(y=a.guid);w=ca(b);N+=
w.length;Pa();return!0};d.mugicPopWin=u;d.mugicRight=u;d.skimlinksReload=function(){K=!1;n();return!0};d.skimlink_legacy_support||(d.skimlinks=qa);Oa()})();