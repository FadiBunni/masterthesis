const mqtt = require('mqtt');
const {google} = require('googleapis');
const spreadsheetId = "16oPsQvQZyJigzm8JCTlcv1ThVHIJtCvd2HtcL_L5jYQ"; 

// MQTT setup
var options = {
    port: 1883,
    clientId: 'mqttjs_' + Math.random().toString(16).substr(2, 8),
    username: 'prgtest@ttn',
    password: 'NNSXS.NBHM4JWOSZA5CTXV5KB3LVNK7EDCYOSIH2JGNSI.4JHXELGCXLWRS47PTL2OD7CA2QSO5IWZTO6IUJWVK4Q7QIG7GB2Q',
    keepalive: 60,
    reconnectPeriod: 1000,
    protocolId: 'MQIsdp',
    protocolVersion: 3,
    clean: true,
    encoding: 'utf8'
};
var client = mqtt.connect('https://eu1.cloud.thethings.network',options);

// Global variable to save data
var globalMQTT = 0;

// MQTT setup
client.on('connect', function() {
    console.log('Client connected to TTN')
    client.subscribe('#')
});

client.on('error', function(err) {
    console.log(err);
});

client.on('message', function(topic, message) {
    var objTTN = JSON.parse(message);
    //console.log("obj from TTN: ", objTTN)
    objTimeStampUplink = objTTN.received_at
    if(objTTN.uplink_message.decoded_payload !== undefined ){
      objDecodedUplink = objTTN.uplink_message.decoded_payload;
    }
    console.log("Timestamp from TTN: ", objTimeStampUplink);
    console.log("Decoded data from TTN: ", objDecodedUplink);

    async function googleSheet (objTimeStampUplink,objDecodedUplink) {

      const auth = new google.auth.GoogleAuth({
        keyFile: "credentials.json",
        scopes: "https://www.googleapis.com/auth/spreadsheets"
      });
    
      // create client instance for auth
      const googleSheetClient = await auth.getClient();
    
      // instance for google sheet API
      const googleSheet = await google.sheets({version: "v4", auth: googleSheetClient});
    
      const postData = await googleSheet.spreadsheets.values.append({
        auth,
        spreadsheetId,
        range: "lorawangatewaylogger",
        valueInputOption: "RAW",
        resource: {
          values: [[
                  objTimeStampUplink,
                  objDecodedUplink.busVoltageBattery,objDecodedUplink.busVoltageOutput,objDecodedUplink.busVoltageSolar,
                  objDecodedUplink.current_mABattery,objDecodedUplink.current_mAOutput,objDecodedUplink.current_mASolar,
                  objDecodedUplink.loadVoltageBattery,objDecodedUplink.loadVoltageOutput,objDecodedUplink.loadVoltageSolar,
                  objDecodedUplink.shuntVoltageBattery,objDecodedUplink.shuntVoltageOutput,objDecodedUplink.shuntVoltageSolar  
          ]]
        }
      });    
      //console.log(metaData.data);
      //console.log(getRows.data)
    }
    
    googleSheet(objTimeStampUplink, objDecodedUplink);
});












