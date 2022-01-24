var mmW = 10;
var ssW = 0;

var tempoW = 1000;//Quantos milésimos valem 1 segundo?
var cronW;

//Inicia o temporizador
function startW() {
    cronW = setInterval(() => { timerW(); }, tempoW);
}

//Para o temporizador mas não limpa as variáveis
function pauseW() {
    clearInterval(cronW);
}

//Para o temporizador e seta as variáveis
function pararW() {
    clearInterval(cronW);
    mmW = 10;
    ssW = 0;

    document.getElementById("counterWhite").innerHTML = '10:00'
}

//Faz a contagem do tempo e exibição
function timerW() {
    if((mmW > 0) || (ssW > 0)){
        if (ssW == 00){
            ssW=59;
            mmW--;
        }
        else{
            ssW--;
        }
    }

    //Cria uma variável com o valor tratado Minutos:Segundos
    var formatoW = (mmW < 10 ? '0' + mmW : mmW) + ':' + (ssW < 10 ? '0' + ssW : ssW);
    
    //Insere o valor tratado no elemento counterWhite
    document.getElementById('counterWhite').innerHTML = formatoW;

    //Retorna o valor tratado
    return formatoW;
}