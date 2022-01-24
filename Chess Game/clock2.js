var mmB = 10;
var ssB = 0;

var tempoB = 1000;//Quantos milésimos valem 1 segundo?
var cronB;

//Inicia o temporizador
function startB() {
    cronB = setInterval(() => { timerB(); }, tempoB);
}

//Para o temporizador mas não limpa as variáveis
function pauseB() {
    clearInterval(cronB);
}

//Para o temporizador e seta as variáveis
function pararB() {
    clearInterval(cronB);
    mmB = 10;
    ssB = 0;

    document.getElementById("counterBlack").innerHTML = '10:00'
}

//Faz a contagem do tempo e exibição
function timerB() {
    if((mmB > 0) || (ssB > 0)){
        if (ssB == 00){
            ssB=59;
            mmB--;
        }
        else{
            ssB--;
        }
    }

    //Cria uma variável com o valor tratado Minutos:Segundos
    var formatoB = (mmB < 10 ? '0' + mmB : mmB) + ':' + (ssB < 10 ? '0' + ssB : ssB);
    
    //Insere o valor tratado no elemento counterBlack
    document.getElementById('counterBlack').innerHTML = formatoB;

    //Retorna o valor tratado
    return formatoB;
}