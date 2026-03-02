const express = require("express");
const http = require("http");
const socketIo = require("socket.io");
const mqtt = require("mqtt");

const app = express();
const server = http.createServer(app);
const io = socketIo(server);

const MQTT_BROKER = "mqtt://localhost";
const MQTT_TOPIC_COMMAND = "device/commands";
const MQTT_TOPIC_SENSOR = "device/sensor";

const mqttClient = mqtt.connect(MQTT_BROKER);

mqttClient.on("connect", () => {
    console.log("Connected to MQTT broker");
    mqttClient.subscribe(MQTT_TOPIC_SENSOR);
});

mqttClient.on("message", (topic, message) => {
    if (topic === MQTT_TOPIC_SENSOR) {
        io.emit("sensorData", message.toString());
    }
});

app.use(express.static("public"));

io.on("connection", (socket) => {
    console.log("Web client connected");

    socket.on("valveCommand", (data) => {
        mqttClient.publish(MQTT_TOPIC_COMMAND, data);
    });
});

server.listen(3000, () => {
    console.log("Server running at http://localhost:3000");
});
