function AlteraEstadoRele(){
    var estado1 = document.getElementById("estado1").innerHTML;
    var estado2 = document.getElementById("estado2").innerHTML;
    if(estado1 === "0"){
        document.getElementById("botao1").innerHTML="1 On";
        document.getElementById("botao1").href="/?ligar1";
    } else {
        document.getElementById("botao1").innerHTML="1 Off";
        document.getElementById("botao1").href="/?desligar1";
    }
    if(estado2 === "0"){
        document.getElementById("botao2").innerHTML="2 On";
        document.getElementById("botao2").href="/?ligar2";
    } else {
        document.getElementById("botao2").innerHTML="2 Off";
        document.getElementById("botao2").href="/?desligar2";
    }
}
