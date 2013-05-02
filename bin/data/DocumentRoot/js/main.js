/*==============================================================================
 
 Copyright (c) 2013- Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

        // <div class="row">
        //   <div class="span4 offset4 text-center">
        //     <h3 id="video-title">Title</h3>
        //     <canvas id="myCanvas" width="320" height="240" style="border:1px solid #d3d3d3;">Your browser does not support the HTML5 canvas tag.</canvas>
        //     <div class="progress progress-striped">
        //       <div id="video-progress" class="bar" style="width: 99%;">
        //         <span id="video-speed">Speed: 0.2</span>
        //       </div>
        //     </div>
        //     <!--
        //             <a class="btn btn-large" href="#"><i class="icon-step-backward"></i></a>
        //             <a class="btn btn-large" href="#"><i class="icon-fast-backward"></i></a>
        //      -->    
        //             <a class="btn btn-large" href="#"><i id="video-backward" class="icon-backward"></i></a>
        //             <a class="btn btn-large" href="#"><i id="video-play"     class="icon-play"    ></i></a>
        //             <a class="btn btn-large" href="#"><i id="video-pause"    class="icon-pause"   ></i></a>
        //             <a class="btn btn-large" href="#"><i id="video-stop"     class="icon-stop"    ></i></a>
        //             <a class="btn btn-large" href="#"><i id="video-forward"  class="icon-forward" ></i></a>
        //     <!--         
        //             <a class="btn btn-large" href="#"><i class="icon-fast-forward"></i></a>
        //             <a class="btn btn-large" href="#"><i class="icon-step-forward"></i></a>
        //      -->

        //   </div>
        // </div>

// commands
var VIDEO_INFO_PROGRESS = "video-info-progress";
var VIDEO_INFO_SPEED    = "video-info-speed";
var VIDEO_INFO_TITLE    = "video-info-title";
var VIDEO_INFO_FRAMES   = "video-info-frames";
var VIDEO_INFO_DURATION = "video-info-duration";

var VIDEO_DATA_PIXELS   = "video-data-pixels";

var VIDEO_CONTROL_BACKWARD = "video-control-backward";
var VIDEO_CONTROL_PLAY     = "video-control-play";
var VIDEO_CONTROL_PAUSE    = "video-control-pause";
var VIDEO_CONTROL_STOP     = "video-control-stop";
var VIDEO_CONTROL_FORWARD  = "video-control-forward";
var VIDEO_CONTROL_POSITION = "video-control-position";


function isCommand(data,command) {
  // essentially "beginsWith()"
  return parseCommand(data,command) === command;
}

function parseName(data) {
  return str.substr(0,str.indexOf(':'));
}

function parseValue(data,command) {
  return str.substr(str.indexOf(':')+1);
}

function prepareMessage(command,data) {
  txt = typeof txt !== 'undefined' ? data : null;
    return JSON.stringify({ command: command, data: txt });
}

function onOpen() {
  ofLogNotice("Connection Opened.");
}

function onMessage(evt) {
  var data = evt.data;

  // var obj = JSON.parse(evt.data);


//  var command = parseCommand()


  // if(isCommand(evt.data,VIDEO_PROGRESS)) {

  // } else if(isCommand(evt.data,VIDEO_SPEED)) {
  //   $("#video-speed").text(evt.data);


  // } else if(isCommand(evt.data,VIDEO_PIXELS)) {

  // } else {

  // }


  $("#number").text(evt.data);
}

function onClose() {
  ofLogNotice("Connection closed.");
}

function onError() {
  ofLogNotice("Connection Error.");
}


$(document).ready( function() {
  // creat the new socket
  var ws = new ofxHTTPWebSocket();//['of','off']);

  // set callbacks
  ws.onOpen    = onOpen;
  ws.onMessage = onMessage;
  ws.onClose   = onClose;
  ws.onError   = onError;

  // button controls
  $("#" + VIDEO_CONTROL_BACKWARD).click(function() {
    console.log("sending bward");
    ws.send(prepareMessage(VIDEO_CONTROL_BACKWARD));  
  });
  
  $("#" + VIDEO_CONTROL_PLAY).click(function() {
    console.log("sending play");
    ws.send(prepareMessage(VIDEO_CONTROL_PLAY));     
  });
  
  $("#" + VIDEO_CONTROL_PAUSE).click(function() { 
    console.log("sending pause");
    ws.send(prepareMessage(VIDEO_CONTROL_PAUSE)); 
  });
  
  $("#" + VIDEO_CONTROL_STOP).click(function() { 
    console.log("sending stop");
    ws.send(prepareMessage(VIDEO_CONTROL_STOP));  
  });
  
  $("#" + VIDEO_CONTROL_FORWARD).click(function() { 
    console.log("sending forward");
    ws.send(prepareMessage(VIDEO_CONTROL_FORWARD));  
  });

  $("#" + VIDEO_CONTROL_POSITION).click(function(evt) {
    var relativeX = evt.pageX - $(this).offset().left;
    var elementWidth = $(this).width();
    var normPosition = ofClamp(relativeX / elementWidth);
    console.log(normPosition);
    ws.send(prepareMessage(VIDEO_CONTROL_POSITION,normPosition));  
  });

  // connect to the port
  ws.connect();

});
