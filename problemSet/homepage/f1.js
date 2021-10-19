function trackSelector() {

    const trackToCornerMap = {
        "australia" : "Turns 11 and 12 because of their speed.",
        "portimao" : "Turn 1.",
        "mexico" : "The S-section",
        "mugello" : "The uphill right-hander.",
        "imola" : "Piratella",
        "monza" : "Ascari",
        "bahrain" : "The downhill easy-to-lockup left-hander",
        "baku" : "Castle Section",
        "barcelona" : "Turn 3",
        "monaco" : "Tabac",
        "spa" : "My favorite circuit of all time. Pouhon",
        "canada" : "Final Chicane",
        "texas" : "Winding right-hander in Sector 3",
        "france" : "Winding right-hander",
        "netherland" : "carousel",
        "hockenheim" : "Hairpin",
        "hungary" : "Blind left-hander up the hill",
        "turkey" : "The crazy complex of left-turns",
        "singapore" : "ex Singapore sling section",
        "nurburgring" : "Turn 1",
        "austria" : "Turn 3",
        "brazil" : "Turn 1",
        "china" : "Snail section",
        "silverstone" : "maggotts-beckets complex",
        "japan" : "the entire circuit... or the s-section"
    }

    var id = document.getElementById("trackSelection").value;

    var keys = Object.keys(trackToCornerMap);

    for (key in keys) {
        if (id === keys[key]) {
            output = trackToCornerMap[id]
        }
    }

    document.querySelector('#feedbackF1').innerHTML = output

}

