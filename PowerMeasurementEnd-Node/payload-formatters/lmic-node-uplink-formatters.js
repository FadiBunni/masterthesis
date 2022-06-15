/*******************************************************************************
 *
 *  File:         lmic-node-uplink-formatters.js
 * 
 *  Function:     LMIC-node uplink payload formatter JavaScript function(s).
 * 
 *  Author:       Fadi Bunni
 * 
 *  Description:  These function(s) are for use with The Things Network V3. 
 *                 
 ******************************************************************************/

 function decodeUplink(input) {
    var data = {};
    var warnings = [];
    
    function bytesToFloat(bytes) {
      // JavaScript bitwise operators yield a 32 bits integer, not a float.
      // Assume LSB (least significant byte first).
      var bits = bytes[3]<<24 | bytes[2]<<16 | bytes[1]<<8 | bytes[0];
      var sign = (bits>>>31 === 0) ? 1.0 : -1.0;
      var e = bits>>>23 & 0xff;
      var m = (e === 0) ? (bits & 0x7fffff)<<1 : (bits & 0x7fffff) | 0x800000;
      var f = sign * m * Math.pow(2, e - 150);
      return f;
    } 

    if (input.fPort == 10) {
        //solar
        data.busVoltageSolar = bytesToFloat(input.bytes.slice(0, 4))
        data.current_mASolar = bytesToFloat(input.bytes.slice(4, 8))
        data.shuntVoltageSolar = bytesToFloat(input.bytes.slice(8, 12))
        data.loadVoltageSolar = bytesToFloat(input.bytes.slice(12, 16))
        //Battery
        data.busVoltageBattery = bytesToFloat(input.bytes.slice(16, 20))
        data.current_mABattery = bytesToFloat(input.bytes.slice(20, 24))
        data.shuntVoltageBattery = bytesToFloat(input.bytes.slice(24, 28))
        data.loadVoltageBattery = bytesToFloat(input.bytes.slice(28, 32))
        //Output(load)
        data.busVoltageOutput = bytesToFloat(input.bytes.slice(32, 36))
        data.current_mAOutput = bytesToFloat(input.bytes.slice(36, 40))
        data.shuntVoltageOutput  = bytesToFloat(input.bytes.slice(40, 44))
        data.loadVoltageOutput  = bytesToFloat(input.bytes.slice(44, 48))
        //Sensor
        data.temperture = bytesToFloat(input.bytes.slice(48,52))
    }else {
        warnings.push("Unsupported fPort");
    }
    
    return {
        data: data,
        warnings: warnings
    };
}