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
            background-color: #b30c0c;
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
            background: #b30c0c;
            cursor: pointer;
        }

        .slider::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: #b30c0c;
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
            <td class="button"></td>
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
        let websocketCamera;
        let streamTimeout;

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
