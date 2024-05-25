/**

  HTML + CSS + JAVA Script


  @
  @
*/


/**static const char PROGMEM INDEX_HTML[] = R"rawliteral(

)rawliteral";*/

const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(


<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
    <style>
        .arrows {
            font-size: 70px;
            color: #673301;
        }

        .circularArrows {
            font-size: 80px;
            color: black;
        }

        table.tb {
            width: 400px;
            margin: auto;
            table-layout: fixed;
            text-align: center
        }

        table.new {
            width: 400px;
            margin: auto;
            text-align: center
        }

        .tb th,
        .tb td {
            border: solid 1px #777;
            padding: 5px;
            background-color: rgb(235, 217, 197);
            border-radius: 25%;
            box-shadow: 5px 5px #888888;
        }

        .tb th {
            background: #3630a3;
            color: white;
            text-align: left;
        }

        .tb td:active {
            transform: translate(5px, 5px);
            box-shadow: none;
        }

        .new td {
            background: #fff;
        }

        .tcell {
            background: #f6f8ff;
        }

        .tlite {
            background: #fff;
        }

        .noselect {
            -webkit-touch-callout: none;
            /* iOS Safari */
            -webkit-user-select: none;
            /* Safari */
            -khtml-user-select: none;
            /* Konqueror HTML */
            -moz-user-select: none;
            /* Firefox */
            -ms-user-select: none;
            /* Internet Explorer/Edge */
            user-select: none;
            /* Non-prefixed version, currently
                                      supported by Chrome and Opera */
        }
    </style>
</head>

<body class="noselect" style="background-color:rgb(77,82,88)">

    <h2 style="color: white;text-align:center;">WI-FI CONTROL &#128662;</h2>
    <h1 style="color: white;text-align:center;">HUMAN MOTION SENSING ROBOT CAR</h1>

    <table class="tb" id="mainTable" CELLSPACING=10>
        <tr>
            <td ontouchstart='onTouchStartAndEnd("control-5")' onmousedown='onControlButton("control-5")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#11017;</span></td>
            <td ontouchstart='onTouchStartAndEnd("control-1")' onmousedown='onControlButton("control-1")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#8679;</span></td>
            <td ontouchstart='onTouchStartAndEnd("control-6")' onmousedown='onControlButton("control-6")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#11016;</span></td>
        </tr>

        <tr>
            <td ontouchstart='onTouchStartAndEnd("control-3")' onmousedown='onControlButton("control-3")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#8678;</span></td>
            <td></td>
            <td ontouchstart='onTouchStartAndEnd("control-4")' onmousedown='onControlButton("control-4")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#8680;</span></td>
        </tr>

        <tr>
            <td ontouchstart='onTouchStartAndEnd("control-7")' onmousedown='onControlButton("control-7")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#11019;</span></td>
            <td ontouchstart='onTouchStartAndEnd("control-2")' onmousedown='onControlButton("control-2")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#8681;</span></td>
            <td ontouchstart='onTouchStartAndEnd("control-8")' onmousedown='onControlButton("control-8")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="arrows">&#11018;</span></td>
        </tr>
        <tr>
            <td ontouchstart='onTouchStartAndEnd("control-9")' onmousedown='onControlButton("control-9")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="circularArrows">&#8634;</span></td>

            <td onclick="onToggle()">
                <span class="circularArrows" id="ledToggleButton"
                    style="font-size:35px;text-shadow:1px 1px 2px #000000;">&#69;&#83;&#80;&#51;&#50;</span>
            </td>

            <td ontouchstart='onTouchStartAndEnd("control-10")' onmousedown='onControlButton("control-10")'
                onmouseup='onControlButtonRelease("control-0")' ontouchend='onTouchStartAndEnd("control-0")'><span
                    class="circularArrows">&#8635;</span></td>
        </tr>
    </table>

    <table class="new">
        <tr>
            <div id="sliders" class="slider-container">
                <td colspan="2">Motor Speed: </td>
                <td><input type="range" id="speed" min="0" max="255" value="200"
                        onchange="onTouchStartAndEnd('speed-' + this.value)"></td>
            </div>
        </tr>

        <tr>
            <td colspan="2">Raw Value: </td>
            <td><span id="demo"></span></td>
        </tr>

        <tr>
            <td colspan="2">Duty Cycle: </td>
            <td><span id="demo1"></span>
                <span>%</span>
            </td>
        </tr>
    </table>

    <script>
        var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
        var websocket;
        var toggleState = 0; //sang 

        window.onload = initWebSocket;
        document.getElementById("ledToggleButton").addEventListener("touchend", function (event) {
            onToggle();
            event.preventDefault()
        });

        function initWebSocket() {
            websocket = new WebSocket(webSocketUrl);
            websocket.onopen = function (event) { };
            websocket.onclose = function (event) { setTimeout(initWebSocket, 2000); };
            websocket.onmessage = function (event) { };
            toggleState = 0;
        }
        function onTouchStartAndEnd(value) {
            websocket.send(value);
            console.log("Pressed button with value: " + value);  // sang
        }
        // สร้างฟังก์ชันสำหรับส่งค่าการควบคุมผ่าน WebSocket
        function sendControlCommand(value) {
            websocket.send(value);
        }
        // สร้างฟังก์ชันสำหรับเมื่อคลิกปุ่ม
        function onControlButton(value) {
            sendControlCommand(value);
            console.log("Pressed button with value: " + value); // sang
        }
        // สร้างฟังก์ชันสำหรับเมื่อปล่อยปุ่ม
        function onControlButtonRelease(value) {
            sendControlCommand(value);
            console.log("Released button: " + value); // sang
        }

        function updateLedToggleButton() {
            var ledToggleButton = document.getElementById("ledToggleButton");
            if (toggleState == 1) {
                ledToggleButton.innerHTML = "&#82;&#80;&#105;"; //Raspberry Pi
            } else {
                ledToggleButton.innerHTML = "&#69;&#83;&#80;&#51;&#50;"; //ESP32
            }
            //ledToggleButton.innerHTML = toggleState ? "&#128162;" : "&#128161;"; // เปลี่ยนไอคอนตามสถานะ

        }

        // ปรับปรุงฟังก์ชัน onToggle ที่มีอยู่เพื่อจัดการปุ่มใหม่
        function onToggle() {
            toggleState = !toggleState;
            //var value = toggleState ? "1" : "0";
            if (toggleState ? "1" : "0")
                updateLedToggleButton();
            onTouchStartAndEnd("control-11");
        }

        var slider = document.getElementById("speed");
        var output = document.getElementById("demo");
        var output1 = document.getElementById("demo1");
        output.innerHTML = slider.value;
        output1.innerHTML = ((slider.value * 100) / 255).toFixed(1);
        slider.oninput = function () {
            output.innerHTML = this.value;
            output1.innerHTML = ((this.value * 100) / 255).toFixed(1);
        }


    </script>
</body>

</html>


)HTMLHOMEPAGE";