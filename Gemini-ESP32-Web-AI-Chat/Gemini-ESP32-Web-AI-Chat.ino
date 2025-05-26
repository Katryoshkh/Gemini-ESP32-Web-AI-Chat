#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="id">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Gemini AI Chat</title>
  <script src="https://cdn.jsdelivr.net/npm/marked/marked.min.js"></script>
  <style>
    * {
      box-sizing: border-box;
    }

    body {
      background: #0f1117;
      color: #e0e0e0;
      font-family: "Segoe UI", Roboto, sans-serif;
      margin: 0;
      padding: 0;
      display: flex;
      flex-direction: column;
      height: 100vh;
    }

    header {
      position: sticky;
      top: 0;
      background: #1a1c23;
      padding: 1rem;
      text-align: center;
      font-size: 1.5rem;
      font-weight: bold;
      color: #00c3ff;
      border-bottom: 1px solid #333;
      z-index: 10;
    }

    #chat {
      flex: 1;
      padding: 1rem;
      padding-bottom: 100px; 
      overflow-y: auto;
      display: flex;
      flex-direction: column;
      gap: 0.75rem;
    }

    .msg {
      line-height: 1.6;
      word-wrap: break-word;
    }

    .user {
      color: #90caf9;
      font-weight: bold;
    }

    .ai {
      color: #a5d6a7;
    }

    footer {
      position: fixed;
      bottom: 0;
      left: 0;
      width: 100%;
      display: flex;
      padding: 0.75rem;
      background: #1a1c23;
      border-top: 1px solid #333;
      gap: 0.5rem;
      flex-wrap: wrap;
      z-index: 100;
    }

    input {
      flex: 1;
      padding: 0.9rem;
      border: none;
      border-radius: 7px;
      background: #22252d;
      color: #e0e0e0;
      font-size: 1rem;
      outline: none;
      min-width: 0;
    }

    button {
      padding: 0.9rem 1.5rem;
      border: none;
      border-radius: 7px;
      background: #00c3ff;
      color: #0f1117;
      font-weight: bold;
      cursor: pointer;
      font-size: 1rem;
      transition: background 0.3s;
    }

    button:hover {
      background: #00a3cc;
    }

    @media (max-width: 500px) {
      header {
        font-size: 1.2rem;
      }

      input {
        font-size: 0.95rem;
        padding: 0.8rem;
      }

      button {
        font-size: 0.95rem;
        padding: 0.8rem 1.2rem;
      }
    }

    .ai h1, .ai h2, .ai h3 {
      color: #82b1ff;
    }

    .ai code {
      background: #1e1e1e;
      padding: 0.2rem 0.4rem;
      border-radius: 5px;
      font-family: monospace;
    }

    .ai pre {
      background: #1e1e1e;
      padding: 1rem;
      border-radius: 7px;
      overflow-x: auto;
    }
  </style>
</head>
<body>
  <header>Gemini AI Chat</header>
  <div id="chat"></div>
  <footer>
    <input type="text" id="input" placeholder="Tulis pertanyaan..." />
    <button onclick="send()">Kirim</button>
  </footer>

  <script>
    const API_KEY = "YOUR_API_KEY";
    const URL = `https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=${API_KEY}`;

    async function send() {
      const inputEl = document.getElementById("input");
      const chat = document.getElementById("chat");
      const input = inputEl.value.trim();
      if (!input) return;

      chat.innerHTML += `<div class="msg user">Kamu: ${input}</div>`;
      inputEl.value = "";
      chat.scrollTop = chat.scrollHeight;

      const body = {
        contents: [{ parts: [{ text: input }] }]
      };

      try {
        const res = await fetch(URL, {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify(body)
        });

        const json = await res.json();
        const reply = json.candidates?.[0]?.content?.parts?.[0]?.text || "[Respons tidak tersedia]";
        const parsedReply = marked.parse(reply);
        chat.innerHTML += `<div class="msg ai">Gemini:<br>${parsedReply}</div>`;
        chat.scrollTop = chat.scrollHeight;

      } catch (err) {
        console.error(err);
        chat.innerHTML += `<div class="msg ai">[Kesalahan saat menghubungi API]</div>`;
        chat.scrollTop = chat.scrollHeight;
      }
    }

    document.getElementById("input").addEventListener("keydown", (e) => {
      if (e.key === "Enter") send();
    });
  </script>
</body>
</html>
)rawliteral";

void handleRoot() {
  server.send_P(200, "text/html", index_html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan ke WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nTerhubung ke WiFi!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server dimulai!");
}

void loop() {
  server.handleClient();
}