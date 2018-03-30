
function makeRect(x,y,w,h,base)
{ 
    var c = document.getElementById("dR"+base).cloneNode();
    c.x.baseVal.value = x;
    c.y.baseVal.value = y;
    c.height.baseVal.value = h;
    c.width.baseVal.value = w;
    return c;
}

function makeLine(x1,y1,x2,y2,base)
{ 
    var c = document.getElementById("dL"+base).cloneNode();
    c.x1.baseVal.value = x1;
    c.y1.baseVal.value = y1;
    c.x2.baseVal.value = x2;
    c.y2.baseVal.value = y2;
    return c;
}

function makeLineArrow(x1,y1,x2,y2,base)
{ 
    var c = document.getElementById("dLA"+base).cloneNode();
    c.x1.baseVal.value = x1;
    c.y1.baseVal.value = y1;
    c.x2.baseVal.value = x2;
    c.y2.baseVal.value = y2;
    return c;
}

function makeText(x,y,txt,base)
{
    var t = document.getElementById("dT"+base).cloneNode();
    t.id = "";
    t.x.baseVal.getItem(0).value = x;
    t.y.baseVal.getItem(0).value = y;
    t.textContent = txt;
    return t;
}

function makeCircle(x,y,r,base)
{ 
    var c = document.getElementById("dC"+base).cloneNode();
    c.cx.baseVal.value = x;
    c.cy.baseVal.value = y;
    c.r.baseVal.value = r;
    return c;
}

function nameNode(DA,x,y,txt,destx,desty)
{
    var base = DA["nvbase"];
    DA.appendChild(makeRect(x,y,45,25,base));
    DA.appendChild(makeRect(x+5,y+5,15,15,base));
    DA.appendChild(makeRect(x+25,y+5,15,15,base));
    DA.appendChild(makeText(x+12,y+17,txt,base));
    if (destx != null)
    { DA.appendChild(makeLineArrow(x+45-12,y+13,destx-6,desty+13,base)); }
    else
    { DA.appendChild(makeLine(x+25,y+5+15,x+25+15,y+5,base));  }
}

function makePointerVar(DA,x,y,name,destx,desty)
{
    var base = DA["nvbase"];
    DA.appendChild(makeText(x-10,y+12,name,base));
    DA.appendChild(makeRect(x,y,15,15,base));
    if (destx != null)
    { DA.appendChild(makeLineArrow(x+7,y+7,destx-6,desty+13,base)); }
    else
    { DA.appendChild(makeLine(x,y+15,x+15,y,base));  }
}

function makeSVGBBase(id)
{
    var svgbase = '\
    <div id="plotDIV'+id+'">\
    <!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">\
    <svg xmlns="http://www.w3.org/2000/svg" \
	     xmlns:xlink="http://www.w3.org/1999/xlink"\
	     version="1.1" \
	     overflow="hidden"\
	     clip="auto"\
	     height="60px"\
	     width="500px"\
	     id="plot"\
	     >\
	  <marker id="triangle'+id+'"\
		  viewBox="0 0 10 10" refX="0" refY="5" \
		  markerUnits="strokeWidth"\
		  markerWidth="4" markerHeight="3"\
		  orient="auto">\
	    <path d="M 0 0 L 10 5 L 0 10 z" />\
	  </marker>\
	  <g style="visibility: hidden;">\
	    <rect\
	       id="dR'+id+'"\
	       x="20px" y="50px"\
	       width="30px" height="10px"\
	       style="fill:rgb(255,255,255); stroke-width:2; stroke:rgb(0,0,0);" />\
	    <text id="dT'+id+'" text-anchor="" x="200" y="200"\
	     style="text-anchor: middle;\
		    font-size: 12px; \
		    font-family: Arial,sans-serif;\
		    "> </text>\
	    <line id="dLA'+id+'" x1="0" y1="0" x2="200" y2="200"\
	     marker-end="url(#triangle'+id+')"\
		  stroke="black" stroke-width="5"\
		  style="stroke:rgb(0,0,0);stroke-width:2;" \
		 />\
	    <line id="dL'+id+'" x1="0" y1="0" x2="200" y2="200"\
		  stroke="black" stroke-width="5"\
		  style="stroke:rgb(0,0,0);stroke-width:2;" \
		 />\
	    <circle id="dC'+id+'" cx="0" cy="0" r="0" style="fill:none;stroke:black;stroke-width:3" />\
	  </g>\
	  <g id="drawarea'+id+'">\
	  </g>\
       </svg>\
      </div>\
';
    document.write(svgbase);
}

/* EXAMPLE */
function drawScene(base)
{
    makeSVGBBase(base)
    var DA = document.getElementById("drawarea"+base);
    DA["nvbase"] = base;
    
    makePointerVar(DA,20,10,"L",100,20);
    nameNode(DA,100,20,"5",175,20);
    nameNode(DA,175,20,"9",250,20);
    nameNode(DA,250,20,"2",325,20);
    nameNode(DA,325,20,"8",400,20);
    nameNode(DA,400,20,"4",null,null);
    var c1 = makeCircle(20+7.5,10+7.5,10,base);
    c1.style.stroke="#ff0000";
    c1.style.strokeOpacity="0.75";
    DA.appendChild(c1);
    
    var c2 = makeCircle(100+25+7.5,20 + 5 +7.5,10,base);
    c2.style.stroke="#0000FF";
    c2.style.strokeOpacity="0.75";
    DA.appendChild(c2);
}
