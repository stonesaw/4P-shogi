var canvas;
var ctx;
var nametbl = [
  "玉","飛","角","金","銀","桂","香","歩",
  ""  ,"竜","馬",""  ,"全","圭","杏","と"
];
var x1 = [ 0, 1, 1, 1, 0,-1,-1,-1, 1,-1];
var y1 = [-1,-1, 0, 1, 1, 1, 0,-1,-2,-2];
var movtbl = [
  [ 1,1,1,1,1,1,1,1,0,0 ],
  [ 2,0,2,0,2,0,2,0,0,0 ],
  [ 0,2,0,2,0,2,0,2,0,0 ],
  [ 1,1,1,0,1,0,1,1,0,0 ],
  [ 1,1,0,1,0,1,0,1,0,0 ],
  [ 0,0,0,0,0,0,0,0,1,1 ],
  [ 2,0,0,0,0,0,0,0,0,0 ],
  [ 1,0,0,0,0,0,0,0,0,0 ],
  [ 0,0,0,0,0,0,0,0,0,0 ],
  [ 2,1,2,1,2,1,2,1,0,0 ],
  [ 1,2,1,2,1,2,1,2,0,0 ],
  [ 0,0,0,0,0,0,0,0,0,0 ],
  [ 1,1,1,0,1,0,1,1,0,0 ],
  [ 1,1,1,0,1,0,1,1,0,0 ],
  [ 1,1,1,0,1,0,1,1,0,0 ],
  [ 1,1,1,0,1,0,1,1,0,0 ]
];
var setup = [
  [  7, 7, 7, 7, 7, 7, 7, 7, 7 ],
  [ -1, 2,-1,-1,-1,-1,-1, 1,-1 ],
  [  6, 5, 4, 3, 0, 3, 4, 5, 6 ]
]
var fontcolor = ["black","maroon"];
var boxcolor = ["LimeGreen","gray","bule","red"];
var fillcolor = ["LimeGreen","Khaki","white","LightPink"];
var psize = 32;
var board = [];
var bw = 19,bh = 11;
var ofsx = 5,ofsy = 1;
var turn = 0;
var startx = -1,starty = -1;
var username = ["ipad","iphone","android"];
var playtbl = ["先手","後手"];

function piece(){
  this.id = -1;
  this.player = 0;
  this.movable = false;
}

function init(){
  canvas = document.getElementById("world");
  canvas.width = 640;
  canvas.height = 400;
  ctx = canvas.getContext('2d');
  ctx.font = "24px 'MS Pゴシック'";
  user = window.navigator.userAgent.toLowerCase();
  for(i=0; i<username.length; i++){
    if(user.indexOf(username[i]) > 0)break;
  }
  if (i > username.length){
    document.addEventListener("touchstart", touchstart);
  } else {
    document.addEventListener("mousedown", mousedown);
  }
  board = new Array(bh);
  for (y=0; y<bh; y++) {
    board[y] = new Array(bw);
    for (x=0; x<bw; x++) {
      board[y][x] = new piece();
    }
  }
  for (y=0; y<3; y++) {
    for (x=0; x<9; x++) {
      board[ofsy+y+6][ofsx+x].id = setup[y][x];
      board[ofsy+y+6][ofsx+x].player = 0;
      board[ofsy+2-y][ofsx+8-x].id = setup[y][x];
      board[ofsy+2-y][ofsx+8-x].player = 1;
    }
  }
  redraw();
}

function touchstart(e){
  if (e.targetTouches.length == 1){
    touch = e.targetTouches[0];
    touchpiece(touch.pageX ,touch.pageY);
  }
}

function mousedown(e){
  touchpiece(e.clientX ,e.clientY);
}

function touchpiece(tx,ty){
  cx = Math.floor((tx-8)/psize);
  cy = Math.floor((ty-8)/psize);
  if (isinside(cx,cy,0,0,bw,bh)==false)return;
  if (startx == -1){
    movestart(cx,cy);
  } else {
    moveend(cx,cy);
    startx = -1;
    redraw();
  }
}

function movestart(cx,cy){
  id = board[cy][cx].id;
  if(id == -1)return;
  player = board[cy][cx].player;
  if(player != turn)return;
  startx = cx;
  starty = cy;
  drawpiece(startx,starty,id,player,2)
  if (isinside(startx,starty,ofsx,ofsy,9,9) == false){
    for (x=ofsx; x<(ofsx+9); x++){
      pawn = 0;
      for (y=ofsy; y<(ofsy+9); y++){
        if(id != 7)break;
        id2 = board[y][x].id;
        player2 = board[y][x].player;
        if((player == player2)&&(id2 == 7)){
          pawn++;
        }
      }
      if(pawn > 0)continue;
      margin = [ 0,0,0,0,0,2,1,1 ];
      flip = 1-(player*2);
      y = ofsy+(player*8)+(margin[id]*flip);
      while(isinside(x,y,ofsx,ofsy,9,9) == true){
        if(board[y][x].id == -1){
          drawpiece(x,y,-1,0,3);
          board[y][x].movable = true;
        }
        y += flip;
      }
    }return;
  }
  for (dir=0; dir<10; dir++){
    x = startx;
    y = starty;
    flip = 1-(player*2);
    while(movtbl[id][dir] > 0){
      x += x1[dir];
      y += y1[dir]*flip;
      if(isinside(x,y,ofsx,ofsy,9,9) == false)break;
      id2 = board[y][x].id;
      player2 = board[y][x].player;
      if((id2 != -1)&&(player == player2))break;
      drawpiece(x,y,id2,player2,3);
      board[y][x].movable = true;
      if(id2 != -1)break;
      if(movtbl[id][dir] == 1)break;
    }
  }
}

function moveend(endx,endy){
  if(board[endy][endx].movable == false)return;
  id = board[starty][startx].id;
  player = board[starty][startx].player;
  if (isinside(startx,starty,ofsx,ofsy,9,9) == true){
    exist1 = isinside(startx,starty,ofsx,ofsy+6*player,9,3);
    exist2 = isinside(endx  ,endy  ,ofsx,ofsy+6*player,9,3);
    if((exist1 == true)||(exist2 == true)){
      if((id < 8)&&(nametbl[id | 8] != "")){
        if(confirm("成りますか？")){
          board[starty][startx].id |= 8;
        }
      }
    }
  }
  if(board[endy][endx].id != -1){
    tx = (1-player)*(bw-3)+1;
    ty = (1-player)*(bh-3)+1;
    tx1 = (player*2)-1;
    ty1 = (player*2)-1;
    for (i=0; i<20; i++){
      x = tx+(i % 3)*tx1;
      y = ty+Math.floor(i/3)*ty1;
      if(board[y][x].id == -1)break;
    }
    board[y][x].id = board[endy][endx].id & 7;
    board[y][x].player = player;
  }
  board[endy][endx].id = board[starty][startx].id;
  board[endy][endx].player = board[starty][startx].player;
  board[starty][startx].id = -1;
  turn ^= 1;
}

function drawpiece(x,y,id,player,color){
  px = x*psize;
  py = y*psize;
  ctx.fillStyle = boxcolor[color];
  ctx.fillRect(px, py, psize, psize);
  ctx.fillStyle = fillcolor[color];
  ctx.fillRect(px+1, py+1, psize-2, psize-2);
  if(id == -1)return;
  ctx.fillStyle = fontcolor[(id >> 3)& 1];
  if(player){
    px = -px-psize;
    py = -py-psize;
    ctx.rotate(Math.PI);
  }
  ctx.fillText(nametbl[id], px+4, py+24,300);
  if(player)ctx.rotate(Math.PI);
}

function isinside(x,y,ax,ay,w,h){
  if((x<ax)||(x>=(ax+w))||(y<ay)||(y>=(ay+h)))return(false);
  return(true);
}

function redraw(){
  for (y=0; y<bh; y++){
    for (x=0; x<bw; x++){
      if (isinside(x,y,ofsx,ofsy,9,9))c=1; else c=0;
      id = board[y][x].id;
      player = board[y][x].player;
      drawpiece(x,y,id,player,c);
      board[y][x].movable = false;
    }
  }
  ctx.fillStyle = fontcolor[0];
  ctx.fillText(playtbl[turn] ,280 ,(1-turn)*318+26,300);
}
