var socket = io();
var userId = prompt("Enter your user name:", "Username");

$('form').submit(function() {
    socket.emit('chat message', {value: $('#m').val(), userId: userId});
    $('#m').val('');
    return false;
});

socket.on('chat message', function(msg) {
    $('#messages').prepend($('<li>'+msg.value+'<span> - '+msg.userId+'</span></li>'));
});

socket.on('sensor data', function(msg) {
    var marker = '';
    var out = '';
    out += '<table style="width:610px">';
    out += '<tr><td>CO:</td><td>' + msg.CO + ' ppm</td>';
    out += '<td>Large:</td>';
    out += '<td>' + msg.Lg + ' ppft<sup>3</sup></td></tr>';
    out += '<tr><td>C<sub>3</sub>H<sub>8</sub>:</td>';
    out += '<td>' + msg.C3H8 + ' ppm</td>';
    out += '<td>Small:</td>';
    out += '<td>' + msg.Sm + ' ppft<sup>3</sup></td></tr>';
    out += '<tr><td>CH<sub>4</sub>:</td>';
    out += '<td>' + msg.CH4 + ' ppm</td>';
    out += '<td>Temp(&degC):</td>';
    out += '<td>' + Math.round(5/9*(msg.Temp - 32)) + '</td></tr>';
    out += '<tr><td>H<sub>2S</sub></td>';
    out += '<td>' + msg.H2S + ' ppm</td>';
    out += '<td>Temp(&degF):</td>';
    out += '<td>' + msg.Temp +'</td></tr>';
    out += '</font></table>';
    $('table').replaceWith(out);
    out = '';
    if(msg.Lat !== '0')
        {
            marker += '' + msg.Lat + msg.Lat_m.replace("0","") + ',' + msg.Lon + msg.Lon_m.replace("0","") + '';
            console.log(marker);
            out += '<map><img src ="https://maps.googleapis.com/maps/api/staticmap?&size=320x335&markers=color:0xB10202%7C' + marker + '&key=AIzaSyBR_XXA3e-I_nA-gnunchc--fqQYJQBjUg"/></map>';
            $('map').replaceWith(out);
        }
});

socket.on('null data', function(msg) {
    var out = '<table style="width:610px">';
    out += '<tr><td>CO:</td><td>-- ppm</td>';
    out += '<td>Large:</td><td>-- ppft<sup>3</sup></td></tr>';
    out += '<tr><td>C<sub>3</sub>H<sub>8</sub>:</td>';
    out += '<td>-- ppm</td>';
    out += '<td>Small:</td>';
    out += '<td>-- ppft<sup>3</sup></td></tr>';
    out += '<tr><td>CH<sub>4</sub>:</td>';
    out += '<td>-- ppm</td>';
    out += '<td>Temp(&degC):</td>';
    out += '<td>--</td></tr>';
    out += '<tr><td>H<sub>2S</sub></td>';
    out += '<td>-- ppm</td>';
    out += '<td>Temp(&degF):</td>';
    out += '<td>--</td></tr>';
    out += '</font></table>';
    $('table').replaceWith(out);
    console.log(out);
})
