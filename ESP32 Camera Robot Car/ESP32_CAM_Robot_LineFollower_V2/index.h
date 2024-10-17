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
        .button1, .button-1, .button-13 {
            border: none;
            color: white;
            padding: 5px 10px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 13px;
            border-radius: 8px;
            box-shadow: rgba(213, 217, 217, .5) 0 2px 5px 0;
            box-sizing: border-box;
            cursor: pointer;
            user-select: none;
            touch-action: manipulation;
            vertical-align: middle;
            width: 100px;
        }
        .button1, .button-1 {
            background-color: #04AA6D;
        }
        .button-13 {
            background-color: #b30c0c;
        }
        .button-1:hover, .button-13:hover {
            background-color: #59e4b1;
        }
        .button-1:focus, .button-13:focus {
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
        }
        .noselect {
            user-select: none;
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
            transition: opacity .2s;
        }
        .slider:hover {
            opacity: 1;
        }
        .slider::-webkit-slider-thumb, .slider::-moz-range-thumb {
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
            height: 550px;
            margin: 0 auto;
            overflow: hidden;
        }
        .responsive-iframe {
            position: absolute;
            width: 640px;
            height: 640px;
            transform: translate(-50%, -50%) rotate(90deg);
            transform-origin: center;
            zoom: 1;
            margin-top: 300px;
            margin-left: -85px;
        }
        .table2 {
            width: 400px;
            table-layout: fixed;
            margin: auto;
        }
    </style>
</head>

<body class="noselect" style="background-color: white; text-align: center;">
    <div class="image-container hidden" id="stream-container">
        <iframe class="responsive-iframe" id="stream" src="" frameborder="0"></iframe>
    </div>
    <table id="mainTable" class="table2" cellspacing="10">
        <tr>
            <td><span class="button1" id="toggle-stream">Start Stream</span></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" data-action="MoveCar" data-value="1"><span class="arrows">&#8679;</span></td>
            <td></td>
        </tr>
        <tr>
            <td class="button" data-action="MoveCar" data-value="3"><span class="arrows">&#8678;</span></td>
            <td class="button" id="modeToggle"><img id="ModeButton" src="data:image/png;base64,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"></td>
            <td class="button" data-action="MoveCar" data-value="4"><span class="arrows">&#8680;</span></td>
        </tr>
        <tr>
            <td></td>
            <td class="button" data-action="MoveCar" data-value="2"><span class="arrows">&#8681;</span></td>
            <td></td>
        </tr>
        <tr>
            <td style="text-align:left"><b>Speed:</b></td>
            <td colspan=2><input type="range" min="0" max="255" value="150" class="slider" id="Speed"></td>
        </tr>
        <tr>
            <td style="text-align:left"><b>LED:</b></td>
            <td colspan=2><input type="range" min="0" max="255" value="0" class="slider" id="LED"></td>
        </tr>
        <tr>
            <td><span id="ledToggle" class="button-13">LED OFF</span></td>
        </tr>
        <tr>
            <td><span class="button-13" onclick="takeshot()">Capture</span></td>
        </tr>
    </table>
    <h1>Screenshot:</h1>
    <div id="output"><img id="capturedImage" alt="Captured Image" /></div>
    <script>
        const view = document.getElementById('stream');
        const streamButton = document.getElementById('toggle-stream');
        let websocketCarInput, websocketCamera;

        function initWebSocket() {
            websocketCarInput = new WebSocket("ws://" + window.location.hostname + "/CarInput");
            websocketCarInput.onopen = () => {
                sendButtonInput("Speed", document.getElementById("Speed").value);
                sendButtonInput("LED", document.getElementById("LED").value);
            };
            websocketCarInput.onclose = () => setTimeout(initWebSocket, 2000);
        }

        function toggleStream() {
            if (websocketCamera) {
                websocketCamera.close();
                websocketCamera = null;
                view.src = '';
                document.getElementById('stream-container').classList.add('hidden');
            } else {
                websocketCamera = new WebSocket('ws://' + window.location.hostname + '/Camera');
                websocketCamera.binaryType = 'arraybuffer';
                websocketCamera.onopen = () => {
                    document.getElementById('stream-container').classList.remove('hidden');
                    streamButton.textContent = 'Stop Stream';
                };
                websocketCamera.onmessage = (event) => {
                    if (event.data instanceof ArrayBuffer) {
                        view.src = URL.createObjectURL(new Blob([event.data], { type: 'image/jpeg' }));
                    }
                };
                websocketCamera.onclose = () => setTimeout(toggleStream, 500);
            }
            streamButton.textContent = websocketCamera ? 'Stop Stream' : 'Start Stream';
        }

        function sendButtonInput(key, value) {
            websocketCarInput.send(`${key},${value}`);
            console.log(`Sending ${key}=${value}`);
        }

       /* function takeshot() {
            const capturedImage = document.getElementById('capturedImage');
            capturedImage.src = view.src;
            document.getElementById('output').appendChild(capturedImage);
        }*/
        function takeshot() {
        if (!view.src) {
            console.error('No image available to capture.');
            return;
        }
        
        // Use a temporary image element to reduce memory usage
        const tempImage = new Image();
        tempImage.onload = function() {
            // Copy the image to the captured image element
            const capturedImage = document.getElementById('capturedImage');
            capturedImage.src = tempImage.src;  // Copy the source URL

            // Clear previous image in output to prevent memory bloat
            const output = document.getElementById('output');
            output.innerHTML = '';  // Clear previous images
            output.appendChild(capturedImage);
        };
        
        // Assign the current view source to the temporary image
        tempImage.src = view.src;
    }
        document.getElementById('mainTable').addEventListener('click', (event) => {
            const action = event.target.getAttribute('data-action');
            const value = event.target.getAttribute('data-value');
            if (action && value) sendButtonInput(action, value);
        });

        streamButton.addEventListener('click', toggleStream);
        document.getElementById('modeToggle').addEventListener('click', () => {
            const modeButton = document.getElementById("ModeButton");
            modeButton.src = modeButton.src.includes('off') ? 'mode-on.png' : 'mode-off.png';
            sendButtonInput("Mode", modeButton.src.includes('on') ? "1" : "0");
        });

        document.getElementById('ledToggle').addEventListener('click', () => {
            const ledToggle = document.getElementById("ledToggle");
            const isLedOn = ledToggle.textContent.includes('ON');
            ledToggle.textContent = isLedOn ? "LED OFF" : "LED ON";
            ledToggle.style.backgroundColor = isLedOn ? '#b30c0c' : '#04AA6D';
            sendButtonInput("led", isLedOn ? "0" : "1");
        });

        initWebSocket();
    </script>
</body>

</html>


)HTMLHOMEPAGE";
