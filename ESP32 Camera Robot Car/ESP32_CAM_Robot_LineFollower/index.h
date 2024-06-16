const char* htmlHomePage PROGMEM = R"HTMLHOMEPAGE(



<!DOCTYPE html>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <style>
        .arrows {
            font-size: 50px;
            text-align: center;
            color: white;
        }

        .button1 {
            background-color: #04AA6D;
            /* Green */
            border: none;
            color: white;
            padding: 5px 10px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 13px;
        }

        td.button {
            background-color: #FF4060;
            border-radius: 10%;
            box-shadow: 5px 5px #888888;
            text-align: center;
        }

        td.button:active {
            transform: translate(5px, 5px);
            box-shadow: none;
            text-align: center;
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
            /* Non-prefixed version, currently supported by Chrome and Opera */
        }

        .slidecontainer {
            width: 100%;
        }

        .slider {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            border-radius: 5px;
            background: #d3d3d3;
            outline: none;
            opacity: 0.7;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slider:hover {
            opacity: 1;
        }

        .slider::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #FF4060;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #FF4060;
            cursor: pointer;
        }

        .hidden {
            display: none;
        }

        .image-container {
            position: relative;
            width: 400px;
            height: 350px;
            text-align: center;
            margin: auto;


        }

        .responsive-iframe {
            position: relative;
            display: block;
            margin-left: auto;
            margin-right: auto;
            margin-top: auto;
            transform: rotate(90deg);

        }
            

    </style>

</head>

<body class="noselect" text-align="center" style="background-color: white;">
    <!-- <div id="stream-container" class="image-container hidden">-->
    <div class="image-container hidden" id="stream-container">
        <center>
            <!-- <iframe id="stream" src="" frameborder="0" width="400" height="288" scrolling="no" display="block"></iframe>-->
            <iframe class="responsive-iframe" id="stream" src="" frameborder="0" width="300" height="400" scrolling="no"
                display="block"></iframe>
        </center>
    </div>
    <table id="mainTable" style="width:400px;table-layout:fixed ; margin-top:40px;margin-left:auto;margin-right:auto;" CELLSPACING=10>
        <tr>
            <td>
                <!--<button id="toggle-stream">Start Stream</button>-->
                <span class="button button1" id="toggle-stream" style="font-size:13px;">Start
                    Stream</span>
            </td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","1")'
                onmousedown='sendButtonInput("MoveCar","1")' ontouchend='sendButtonInput("MoveCar","0")'
                onmouseup='sendButtonInput("MoveCar","0")'><span class="arrows">&#8679;</span></td>
            <td></td>
        </tr>
        <tr>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","3")'
                onmousedown='sendButtonInput("MoveCar","3")' ontouchend='sendButtonInput("MoveCar","0")'
                onmouseup='sendButtonInput("MoveCar","0")'><span class="arrows">&#8678;</span></td>
            <td class="button" onclick="onToggle()">
                
               
                    <img id="ledToggleButton" src="data:image/png;base64,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">
                <!-- style="font-size:35px;text-shadow:1px 1px 2px #000000;">&#69;&#83;&#80;&#51;&#50; -->
            </td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","4")'
                onmousedown='sendButtonInput("MoveCar","4")' ontouchend='sendButtonInput("MoveCar","0")'
                onmouseup='sendButtonInput("MoveCar","0")'><span class="arrows">&#8680;</span></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" ontouchstart='sendButtonInput("MoveCar","2")'
                onmousedown='sendButtonInput("MoveCar","2")' ontouchend='sendButtonInput("MoveCar","0")'
                onmouseup='sendButtonInput("MoveCar","0")'><span class="arrows">&#8681;</span></td>
            <td></td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Speed:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="150" class="slider" id="Speed"
                        oninput='sendButtonInput("Speed",value)'>
                </div>
            </td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Light:</b></td>
            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="0" class="slider" id="Light"
                        oninput='sendButtonInput("Light",value)'>
                </div>
            </td>
        </tr>
    </table>

    <script>
        const view = document.getElementById('stream');
        const viewContainer = document.getElementById('stream-container');
        const streamButton = document.getElementById('toggle-stream');

        var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";
        var websocketCarInput;
        //var value = 0;
        var toggleState = 0; //sang 
        let websocketCamera;
        let streamTimeout;
        window.onload = initCarInputWebSocket;
        document.getElementById("ledToggleButton").addEventListener("touchend", function (event) {
            onToggle();
            event.preventDefault()
        });
        function initCarInputWebSocket() {
            websocketCarInput = new WebSocket(webSocketCarInputUrl);
            websocketCarInput.onopen = function (event) {
                var speedButton = document.getElementById("Speed");
                sendButtonInput("Speed", speedButton.value);
                console.log("Speed value: " + value); // sang
                var lightButton = document.getElementById("Light");
                sendButtonInput("Light", lightButton.value);
                console.log("Light value: " + value); // sang
            };
            websocketCarInput.onclose = function (event) { setTimeout(initCarInputWebSocket, 2000); };
            websocketCarInput.onmessage = function (event) { };
            toggleState = 0;
        }

        const stopStream = () => {
            if (websocketCamera) {
                websocketCamera.close();
                websocketCamera = null;
            }
            view.src = '';
            viewContainer.classList.add('hidden');
            streamButton.innerHTML = 'Start Stream';
            streamButton.style.color = "white";
            streamButton.style.backgroundColor = "#04AA6D";
        };

        const startStream = () => {
            if (!websocketCamera || websocketCamera.readyState === WebSocket.CLOSED) {
                const webSocketUrl = 'ws://' + window.location.hostname + '/Camera';

                // Create a new WebSocket instance
                websocketCamera = new WebSocket(webSocketUrl);
                websocketCamera.binaryType = 'arraybuffer'; // Receive data as ArrayBuffer

                websocketCamera.onopen = () => {
                    console.log('WebSocket connection opened');
                    viewContainer.classList.remove('hidden');
                    streamButton.innerHTML = 'Stop Stream';
                    streamButton.style.color = 'white';
                    streamButton.style.backgroundColor = '#b30c0c';
                };

                websocketCamera.onmessage = (event) => {
                    if (event.data instanceof ArrayBuffer) {
                        // Convert received ArrayBuffer to Blob
                        const blob = new Blob([event.data], { type: 'image/jpeg' });

                        // Create object URL from Blob and set it as image source
                        const imageUrl = URL.createObjectURL(blob);
                        view.src = imageUrl;
                    }
                };

                websocketCamera.onclose = () => {
                    console.log('WebSocket connection closed');
                    setTimeout(() => {
                        stopStream();
                    }, 500); // Add a delay of 500 milliseconds before stopping the stream
                };

                websocketCamera.onerror = (error) => {
                    console.error('WebSocket error occurred:', error);

                    // Check the readyState of WebSocket to determine the error state
                    if (websocketCamera.readyState === WebSocket.CLOSED) {
                        console.log('WebSocket connection is closed.');
                    } else {
                        console.log('WebSocket encountered an error while open.');
                        setTimeout(() => {
                            handleWebSocketError(error);
                        }, 500); // Add a delay of 500 milliseconds before handling the error
                    }
                };
            } else {
                console.warn('WebSocket is already open or in connecting state.');
            }
        };


        // Function to handle WebSocket errors
        function handleWebSocketError(error) {
            // Display user-friendly error message or perform additional error handling
            console.error('WebSocket error:', error);
            stopStream(); // Stop stream on WebSocket error
        }

        const debouncedStopStream = () => {
            clearTimeout(streamTimeout);
            streamTimeout = setTimeout(() => {
                stopStream();
            }, 500); // Adjust the delay as needed
        };

        const debouncedStartStream = () => {
            clearTimeout(streamTimeout);
            streamTimeout = setTimeout(() => {
                startStream();
            }, 500); // Adjust the delay as needed
        };
        streamButton.addEventListener('click', function () {
            if (streamButton.innerHTML === 'Stop Stream') {
                debouncedStopStream();
            } else {
                debouncedStartStream();
            }
        });
        streamButton.addEventListener('touchstart', function (event) {
            event.preventDefault(); // Prevent default touch behavior
            // Handle touch start event if needed
        });
        function onToggle() {
            toggleState = !toggleState;
            //var value = toggleState ? "1" : "0";
            if (toggleState ? 1 : 0)
                updateLedToggleButton();
                if(toggleState == 1){
                    sendButtonInput("Mode","1");
                }
               else {
                sendButtonInput("Mode","0");
               }
        }
        function updateLedToggleButton() {
            var ledToggleButton = document.getElementById("ledToggleButton");
            if (toggleState == "1") {
               ledToggleButton.src = "data:image/png;base64,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";
            } else {
               ledToggleButton.src = "data:image/png;base64,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";
                
            }
            //ledToggleButton.innerHTML = toggleState ? "&#128162;" : "&#128161;"; // เปลี่ยนไอคอนตามสถานะ

        }


        streamButton.addEventListener('touchend', function (event) {
            event.preventDefault(); // Prevent default touch behavior
            if (streamButton.innerHTML === 'Stop Stream') {
                debouncedStopStream();
            } else {
                debouncedStartStream();
            }
        });
        function sendButtonInput(key, value) {
            // Implement sending button input via WebSocket if needed
            var data = key + "," + value;
            websocketCarInput.send(data);
            console.log(`Sending ${key}=${value}`);
        }
        window.onload = function () {
            initCarInputWebSocket();
            // Other initialization code...
        };
        // Prevent default touchend behavior to avoid unintended scrolling on touch devices
        document.getElementById('mainTable').addEventListener('touchend', (event) => {
            event.preventDefault();
        });
        


    </script>
</body>

</html>








)HTMLHOMEPAGE";
