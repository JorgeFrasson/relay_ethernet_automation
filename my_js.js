function AlteraEstadoRele(){
    var estado1 = document.getElementById("estado1").innerHTML;
    var estado2 = document.getElementById("estado2").innerHTML;
    if(estado1 === "0"){
        document.getElementById("estado1").innerHTML="1";
        document.getElementById("rele1").href="?desligar1";
    } else {
        document.getElementById("estado1").innerHTML="0";
        document.getElementById("rele1").href="?ligar1";
    }
    if(estado2 === "0"){
        document.getElementById("estado2").innerHTML="1";
        document.getElementById("rele2").href="?desligar2";
    } else {
        document.getElementById("estado2").innerHTML="0";
        document.getElementById("rele2").href="?ligar2";
    }
}
