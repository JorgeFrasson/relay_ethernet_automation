function AlteraEstadoRele(){
    var estado1 = document.getElementById("estado1").innerHTML;
    var estado2 = document.getElementById("estado1").innerHTML;
    if(estado1 === "0"){
        document.getElementById("estado1").innerHTML="1";
        document.getElementById("rele1").innerHTML="<div class='rele_ligado'></div>";
        document.getElementById("botao1").innerHTML="<a href='/?desligar1' class='botao'>Desligar Rele</a>";
    } else {
        document.getElementById("estado").innerHTML="0";
        document.getElementById("rele1").innerHTML="<div class='rele_desligado'></div>";
        document.getElementById("botao1").innerHTML="<a href='/?ligar1' class='botao'>Ligar Rele</a>";
    }
    if(estado2 == "0"){
        document.getElementById("estado2").innerHTML="1";
        document.getElementById("rele2").innerHTML="<div class='rele_ligado'></div>";
        document.getElementById("botao2").innerHTML="<a href='/?desligar2' class='botao'>Desligar Rele</a>";
    } else {
        document.getElementById("estado2").innerHTML="0";
        document.getElementById("rele2").innerHTML="<div class='rele_desligado'></div>";
        document.getElementById("botao2").innerHTML="<a href='/?ligar2' class='botao'>Ligar Rele</a>";
    }
}
