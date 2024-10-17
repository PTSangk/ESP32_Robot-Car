const char *htmlHomePage PROGMEM = R"HTMLHOMEPAGE(


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
 .button-row {
    display: flex;
    justify-content: space-around; /* Distribute space evenly */
    gap: 20px; /* Adjust the gap between buttons */
    margin: 10px 0;
  }
        .button1 {
            background-color: #04AA6D;
            border: none;
            color: white;
            padding: 5px 10px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 13px;
        }

        /* update for led onoff */
        .button-1 {
            background-color: #04AA6D;
            border: 1px solid #d5d9d9;
            border-radius: 8px;
            box-shadow: rgba(213, 217, 217, .5) 0 2px 5px 0;
            box-sizing: border-box;
            color: #ffffff;
            cursor: pointer;
            display: inline-block;
            font-family: "Amazon Ember", sans-serif;
            font-size: 13px;
            line-height: 29px;
            padding: 0 10px 0 11px;
            position: relative;
            text-align: center;
            text-decoration: none;
            user-select: none;
            -webkit-user-select: none;
            touch-action: manipulation;
            vertical-align: middle;
            width: 100px;

        }

        .button-1:hover {
            background-color: #59e4b1;
        }

        .button-1:focus {
            border-color: #008296;
            box-shadow: rgba(213, 217, 217, .5) 0 2px 5px 0;
            outline: 0;
        }

        .button-13 {
            background-color: #b30c0c;
            border: 1px solid #d5d9d9;
            border-radius: 8px;
            box-shadow: rgba(213, 217, 217, .5) 0 2px 5px 0;
            box-sizing: border-box;
            color: #ffffff;
            cursor: pointer;
            display: inline-block;
            font-family: "Amazon Ember", sans-serif;
            font-size: 13px;
            line-height: 29px;
            padding: 0 10px 0 11px;
            position: relative;
            text-align: center;
            text-decoration: none;
            user-select: none;
            -webkit-user-select: none;
            touch-action: manipulation;
            vertical-align: middle;
            width: 100px;

        }

        .button-13:hover {
            background-color: #59e4b1;
        }

        .button-13:focus {
            border-color: #008296;
            box-shadow: rgba(213, 217, 217, .5) 0 2px 5px 0;
            outline: 0;
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
            width: 700px;
            max-width: 100%;
            /* Max width to match the new width after rotation */
            height: 550px;
            margin: 0 auto;
            /* Center the container horizontally */
            overflow: hidden;
        }

        .responsive-iframe {
            position: absolute;
            width: 640px;
            height: 640px;

            overflow: hidden;
            transform: translate(-50%, -50%) rotate(90deg);
            transform-origin: center;
            zoom: 1;
            margin-top: 300px;
            margin-left: -85px;
            margin-right: auto;
        }

        .table2 {
            padding-top: auto;
            position: relative;
            width: 400px;
            table-layout: fixed;
            margin-top: auto;
            margin-left: auto;
            margin-right: auto;
        }
    </style>

</head>

<body class="noselect" style="background-color: white; text-align: center;">
    <!-- <div id="stream-container" class="image-container hidden">-->
    <div class="image-container hidden" id="stream-container">
        <center>
            <!-- <iframe id="stream" src="" frameborder="0" width="400" height="288" scrolling="no" display="block"></iframe>-->
            <iframe class="responsive-iframe" id="stream" src="" frameborder="0"></iframe>
        </center>
    </div>
    <table id="mainTable" class="table2" CELLSPACING=10>
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


                <img id="ModeButton"
                    src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAHYAAAB2AH6XKZyAAAAGXRFWHRTb2Z0d2FyZQB3d3cuaW5rc2NhcGUub3Jnm+48GgAACJFJREFUeJzdm11sVMcVx39nds3a2GbB2A7fEAwE1sR2Sp8itRiE1Ne+8BJQIFUa9Y2Qir4G0SqVUJVGbaW8tCAIeaKPlaKK1oBxCBhcSAlNTL5IAEMBg9fe9X7c3Z0+rNdee+/cnWuzBvcvWfLdOzPn/z97zsyZ2XsFn9CdB4Pob34EgU7QP0T0BpDFwEJA/I43TWhgCPQgSD9a+hB9Gtb0yJmDGT8DWRPWP35tJYp9oHcDz/llPEu4B/oESr8nXcfv2HQo6wC9440wjnMI9C8Q5s2c46wgBbxPjfO2fPThsFdDTwfozp/tgNxxYOmTZDdr0AxAbrecPX7a1EQZ+27dewCd+ztzVTyAsAxRp/TW1/abmrg6QG/b8w7CYcTsoDmEAKLf1Z17fu12syQF9Na9BxAOV57XU4CWt+Ts0d8XfzTJAXrrq9sQdQoIzCqx2YImh6ifyJkj/yh8NO4AveONMJn058zlnLfDHWqcSGF1mMhxxznE/794gOUkgwcLFwKgO19fgc58PYfW+Zkihcq1SNfxO8H8dfZNK/GLwvAX18l0Apks1376c1782xEActEYt195k1Wh+f4o1tbAsd+CUmRuDfBw/zss+eufynb7btd+Viey5ZqF0Gof8CulOw8GQe/yx84MDfQnJoovFa7jRuN8bqXi/gaKrAOVz9CM1nyZ8CzoxjHopPg2GbMhulvv3BlQ+Y0NS/yx84ZMWV0bOzbTNzLIndSo/SCtLeP/ZrX2ZXvQSfJdeScs5X7tywqlttmzsoEuKS6aXmoFoG9kkNu2kRBZP+nSdtempOCEFN8ny9gStitybLEc2wqaUrKN7ZsRyX96NfaofCTUhOD55UU8S6PKBCn8ifAokyqXelsUwnqvFtPBVLKhRWEWrFrBmA/4NPaIAS8nbGqBwOQqXCxDoCC+4IjHTtor6jYooNluaHu4cW18afP4NykiXIs/5m464T5A6zqrMV1tF4nP24KhTNrk8GYF1FmObQ1x+boWd7QiCEom4uOz+GPuuTkh0lLyke8UGBNf+H8ok3ZxuK5XVKDud6O6uKN1XHxxTl+PD012wrwqaFlpNabJ9lTxhbSIZtJTHC7Bimx33ciGGhZRt3JZCUGAz0ej/LdAbONaCAZLx7SeA9zFFxw/nHEmbOFxIDITmMK1YSwNphIE+GI0yv100pj/1oeXHuILtkeyTt4WlXKAgW1D+2bjtwPQn4jiRNa6j2lr22Vst7SIZR0eOslKRYA7Gn7Q6klQVc0jsGG1YUzbSbC8+ML9eDbz5B3gVbSEGhYxf/lSI8EFretRVW57Mpl2HWASr8auKxIByoNtQ0erkWC4PWLsZx0BPsSLVGwSNGNRe6uRYPjFjcbx/M0BduKFp+CAhR0RV4KqKkh9ZIN5TMsc8CO+Ying5YJQ02Jqlj1XQrD+hXWokOFMRvxEgL34CkZAFp0z7+EXtpeuBuE29/CfGNPStg/xhXtPHNrJEL3eb7y/sG1TyXK1oKPV2D5585b9JIi9+ApGgPCg+4LxfrhQDxRIBALURcy78ujZS9bLID7EV3QSfNB9EQxHWaGmRqqXNI2TqF33PIGaate2uVSa2OVP/a0CluIrNgmKCOkHg4zc+MbYJtw+sRqEOzYZ241c+Bc6mbJPAR/iK1oHCPCw+6KxzYK2SP4bEKhvMxdA0e7ecQE28CO+oikgCIPnPBzQvgkloFSAulb39T+XShO/fG18PDvb9uIrlwJjRpJ37jH67feubUJLmwk1NzK/ZRWBOvcfTUY+GQt/sY+ASUIpXxpXbDs8EQW9xnb1bRupb/PI/3O9kwRY2cZefMXqgGIjj7q9HBChzlD/55Ip4n2fTRJgZ9tevAClZ09PAMVGEjdvkbw9QPWKZSXt6tojxvCPXbwyNvtPCLCzbS++spNgkZFH5y65tgstaya4wP1QeqS7t0SArXFb8RWtA4qNDPWY08ANuWSK+KVrJQKsbGMvvuJ1QGGdT9y4Serufev+sQtXIO24Hp7a2X5G6oDCD5UCRM/3WfePnbvkKsDO9jNSBxSLFxGiHsthMXKJJKNFxU+xACvbfsSPLYNlH6fwi6niBRj94iucwcdl+8YvXIV0elL/QnlrAz/iBZ1RgMXjFP7gSiAHwx9fLts31tPrKt7XL0NTbbuKB0GNKMB+drKm4E5guMfbAblEksTl667ifU2CVuJB0A8UcGN6Qj1IGAgkrvWTGTI/6zNaCH/DlnYmtkvFCwrVr9BiPz1bwkSAXC6/xBkQH6v9TVvamdieKl4EULpP5d+0eLLwWotHetyrwlwiSaLvuud+3t5+efECoFWXgjU9wL2ZCC5HoDgvE1f/QzZW+sjK6CdXEMfx7Dsd2ybxomUg2Bw/r/Lv2OgTNoPbPqzmtRaTyTHa+++SPqM9lzzFT6cOMIpHECUfyMmT2XwkdL6+AjJfAaFyBm4mYzx0kq4Eywkw3fd7jOVvqXPpK6RUVWCtnDoyoADkzJ9vA+/beHhNdR1NVdVzV3xexh/l1JEBKN4L1Dhv59+xKY/V1XU0Fpwwx8SLcFs5gUMFLeMOkI8+HEbJK1iWxquqa2msCs0t8UhOlNojHx8ZKXEAgJw+ehYtB2wcALAiVEtD1by5IV4EUXq/dB3tKtZQshvMv1Ojf+PLCcHQsy9eyyE5fewPJXpNwvS2vW+hOYzlc4R30wmimfQzKJ6MCL90E+/pABh/ieoDYLlXuwLupRMMZ0pPcp7mhCeKXdJ1rNvE2fNARM4eP02NE0HzLvnXUT2xZF4N4WDV0xcvJBF+J04g4iUeykRAMfT2V5ej1T40uynzctX9dJJY1pl98VoGRNQJlXPek3Mn7trosnbAuCN27gxwv/ZlhO3AFjQvIDShCVN0xPbQSRLPZiojXpMTkaigHyiRG4jqQ/PPYHP8vJw86euE63+K5YXZnOtnxQAAAABJRU5ErkJggg==">
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
            <td style="text-align:left"><b>LED:</b></td>

            <td colspan=2>
                <div class="slidecontainer">
                    <input type="range" min="0" max="255" value="0" class="slider" id="Light"
                        oninput='sendButtonInput("Light",value)'>
                </div>
            </td>
        </tr>
        
        
        <tr>
            <td onclick="updateLedstatus()">

                <span id="ledToggle" class="button-13">LED OFF</span>
            </td>

            <td onclick="takeshot()">

                <span class="button-13">Capture</span>
            </td>
            <td >
                <span id="downloadBtn" class="button-13">Download</span>
            </td>
        </tr>
    </table>
    <h3>Screenshot:</h3>
    <div id="output"><img id="capturedImage" /></div>
    
    <script>
   
        const view = document.getElementById('stream');
        const capturedImage = document.getElementById('capturedImage');  // Reuse single image element
        const viewContainer = document.getElementById('stream-container');
        const streamButton = document.getElementById('toggle-stream');

        var webSocketCarInputUrl = "ws:\/\/" + window.location.hostname + "/CarInput";
        var websocketCarInput;
        var ValueLEDButtonToggleState = 0; //update for led on/off
        var ModeButtonToggleState = 0;
        let websocketCamera;
        let streamTimeout;
        let pingInterval;
        let lastImageDataUrl = '';  // Store the last captured image data URL
        window.onload = initCarInputWebSocket;
        document.getElementById("ModeButton").addEventListener("touchend", function (event) {
            onToggle();
            event.preventDefault()
        });
        function initCarInputWebSocket() {
            websocketCarInput = new WebSocket(webSocketCarInputUrl);
            websocketCarInput.onopen = function (event) {
                var speedButton = document.getElementById("Speed");
                sendButtonInput("Speed", speedButton.value);
                console.log("Speed value: " + value); // sang
                var LEDButton = document.getElementById("LED");
                sendButtonInput("LED", LEDButton.value);
                console.log("LED value: " + value); // sang
                /* 30 June 2024 OFF
               var lightButton = document.getElementById("Light");
               sendButtonInput("Light", lightButton.value);
               console.log("Light value: " + value); // sang
               */
            };
            websocketCarInput.onclose = function (event) { setTimeout(initCarInputWebSocket, 2000); };
            websocketCarInput.onmessage = function (event) { };
            ModeButtonToggleState = 0;
            ValueLEDButtonToggleState = 0;
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
            //viewContainer.classList.remove('hidden');
            //view.src = "C:\Users\Acer\OneDrive\Desktop\Sank\ESP32-CAMERA\ESP32_CAM\images.jpg";
            if (!websocketCamera || websocketCamera.readyState === WebSocket.CLOSED) {
                const webSocketUrl = 'ws://' + window.location.hostname + '/Camera';

                // Create a new WebSocket instance
                websocketCamera = new WebSocket(webSocketUrl);
                websocketCamera.binaryType = 'arraybuffer'; // Receive data as ArrayBuffer

                websocketCamera.onmessage = (event) => {
                    if (event.data instanceof ArrayBuffer) {
                        const blob = new Blob([event.data], { type: 'image/jpeg' });
                        const imageUrl = URL.createObjectURL(blob);
                        view.src = imageUrl;

                        // Revoke the object URL after it's used to free up memory
                        view.onload = () => URL.revokeObjectURL(imageUrl);
                    }
                };



                    websocketCamera.onopen = () => {
                        console.log('WebSocket connection opened');
                        viewContainer.classList.remove('hidden');
                        streamButton.innerHTML = 'Stop Stream';
                        streamButton.style.color = 'white';
                        streamButton.style.backgroundColor = '#b30c0c';

                        // Send a ping every 30 seconds to keep the connection alive
                        pingInterval = setInterval(() => {
                            if (websocketCamera.readyState === WebSocket.OPEN) {
                                websocketCamera.send('ping');
                            }
                        }, 30000); // 30 seconds interval
                    };

                    websocketCamera.onclose = () => {
                        console.log('WebSocket connection closed');
                        clearInterval(pingInterval); // Clear the keep-alive interval
                        setTimeout(stopStream, 500);
                    };


                     websocketCamera.onerror = (error) => {
                        console.error('WebSocket error occurred:', error);

                        if (websocketCamera.readyState === WebSocket.CLOSED) {
                            console.log('WebSocket connection is closed. Attempting to reconnect...');
                            setTimeout(startStream, 1000); // Retry after 1 second
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
                capturedImage.src = '';
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
            ModeButtonToggleState = !ModeButtonToggleState;
            //var value = ModeButtonToggleState ? "1" : "0";
            if (ModeButtonToggleState ? "1" : "0")
                updateModeButton();
            if (ModeButtonToggleState == "1") {
                sendButtonInput("Mode", "1"); // change mode to auto / line follower
                sendButtonInput("Speed", "95"); //add speed  PWM 95
                sendButtonInput("LED", "0"); //add LED  PWM 0
                sendButtonInput("MoveCar", "0") // stop car 
            }
            else {
                sendButtonInput("Mode", "0"); // change mode to manual
                sendButtonInput("MoveCar", "0") // stop car 
                sendButtonInput("LED", "0"); //add LED  PWM 0
            }
        }
        function updateModeButton() {
            var ModeButton = document.getElementById("ModeButton");
            if (ModeButtonToggleState == "1") {
                ModeButton.src = "data:image/png;base64,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";
            } else {
                ModeButton.src = "data:image/png;base64,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";

            }
            //ModeButton.innerHTML = ModeButtonToggleState ? "&#128162;" : "&#128161;"; // ����¹�ͤ͹���ʶҹ�

        }
        //update for led on/off
        function updateLedstatus() {
            var ledToggle = document.getElementById("ledToggle");
            ValueLEDButtonToggleState = !ValueLEDButtonToggleState;
            if (ValueLEDButtonToggleState ? "1" : "0");
            if (ValueLEDButtonToggleState == "0") {
                ledToggle.innerHTML = "LED OFF";
                ledToggle.style.backgroundColor = '#b30c0c';
                sendButtonInput("led", "0");
            } else {
                ledToggle.innerHTML = "LED ON";
                ledToggle.style.backgroundColor = '#04AA6D';
                sendButtonInput("led", "1");

            }
            //update for led on/off 
            //ledToggle.style.color = 'white';
            //ledToggle.style.backgroundColor = '#b30c0c';
        }
        async function takeshot() {
            try {
                const stream = document.getElementById('stream');
                const capturedImage = document.getElementById('capturedImage');

                if (!stream?.src) {
                    console.error('No stream available.');
                    return;
                }

                // Create a temporary image element to ensure the stream is ready
                const tempImage = new Image();
                tempImage.crossOrigin = 'anonymous';  // Handle CORS if needed
                tempImage.src = stream.src;

                // Wait for the image to fully load
                await tempImage.decode();

                // Create a canvas to capture the stream’s frame
                const canvas = document.createElement('canvas');
                const context = canvas.getContext('2d');
                canvas.width = stream.naturalWidth || 640/2;
                canvas.height = stream.naturalHeight || 480/2;

                // Draw the image onto the canvas
                context.drawImage(tempImage, 0, 0, canvas.width, canvas.height);

                // Convert the canvas to a data URL
                lastImageDataUrl = canvas.toDataURL('image/png');
                capturedImage.src = lastImageDataUrl;
            } catch (error) {
                console.error('Error capturing image:', error);
            }
        }

        // Set up the download button functionality
        document.getElementById('downloadBtn').onclick = function () {
            if (!lastImageDataUrl) {
                console.error('No image available to download.');
                return;
            }

            const link = document.createElement('a');
            link.href = lastImageDataUrl;
            link.download = 'esp32_capture.png';
            link.click();
        };
         
        // Set up the download button functionality
        document.getElementById('downloadBtn').onclick = function () {
            if (!lastImageDataUrl) {
                console.error('No image available to download.');
                return;
            }

            const link = document.createElement('a');
            link.href = lastImageDataUrl;
            link.download = 'esp32_capture.png';
            link.click();
        };

        // Set up the download button functionality
        document.getElementById('downloadBtn').onclick = function () {
            if (!lastImageDataUrl) {
                console.error('No image available to download.');
                return;
            }

            const link = document.createElement('a');
            link.href = lastImageDataUrl;
            link.download = 'esp32_capture.png';
            link.click();
        };
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
        }
        // Prevent default touchend behavior to avoid unintended scrolling on touch devices
        document.getElementById('mainTable').addEventListener('touchend', (event) => {
            event.preventDefault();
        });
    </script>
</body>

</html>
)HTMLHOMEPAGE";
