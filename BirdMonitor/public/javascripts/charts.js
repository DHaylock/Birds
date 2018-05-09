// Make the Data Object 
var monitoring = {
   times: [],
   volumes: [],
   events: []
};

var place = "Watershed";

//--------------------------------------------------------------------
// * GET the stuff
//--------------------------------------------------------------------
$.getJSON("./api/v1/get?where=" +place, function(json) {
    // console.log(json);
    $.each(json,function(key,data) {

        if(data.event == "Activated") {
            monitoring.events.push(data.volume);
        } else {
            monitoring.events.push(0);
        }

        monitoring.times.push(data.created_at);
        monitoring.volumes.push(data.volume);
    });

    setTimeout(1500, makeChart());
});

//--------------------------------------------------------------------
// * Make the Chart which shows the activity and volume over time
//--------------------------------------------------------------------
function makeChart() {
    var ctx = document.getElementById('chart').getContext('2d');
    var chart = new Chart(ctx, {
        type: 'bar',
        responsive:true,
        data: {
            labels: monitoring.times,
            datasets: [{
                label: "Activations",
                backgroundColor: '#fbc531',
                borderColor: '#e1b12c',
                data: monitoring.events
            },{
                label: "Volume",
                backgroundColor: '#487eb0',
                borderColor: '#353b48',
                data: monitoring.volumes,
                type:'line'
            }]
        },
        options: {
            barPercentage:0.5
        }
    });
}
