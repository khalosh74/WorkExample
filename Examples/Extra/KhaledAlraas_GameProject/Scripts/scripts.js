//--------------------------------------****Get Buttons****-------------------------------------------
const informationButton = document.getElementById('info-btn')
const startButton = document.getElementById('start-btn')
const restartButtonLose = document.getElementById('restart-btn-lose')
const backButton = document.getElementById('back-btn1')
const restartButtonWin = document.getElementById('restart-btn-win')
const allGameElements = document.getElementById('all')
const controllers = document.getElementById('controllers')
const menu = document.getElementById('menu')
const elStatus = document.getElementById('elStatus')
const co2Status = document.getElementById('co2Status')
const winElement = document.getElementById('win')
const loseElement = document.getElementById('lose')
const whyLost = document.getElementById('whyLost')
//--------------------------------------****Get Displays****-------------------------------------------
const displayCoal = document.getElementById('displayCoal')
const displayOil = document.getElementById('displayOil')
const displayNaturalGas = document.getElementById('displayNaturalGas')
const displayWind = document.getElementById('displayWind')
const displaySolar = document.getElementById('displaySolar')
const displayHydroelectric = document.getElementById('displayHydroelectric')
const displayElSum = document.getElementById('displayElSum')
const displayCo2Sum = document.getElementById('displayCo2Sum')
const displayPopulation = document.getElementById('displayPopulation')
const displayMoney = document.getElementById('displayMoney')
const infoDisplay = document.getElementById('infoDisplay')
//--------------------------------------****Get Factories + put properties****-------------------------------------------
const addCoal = document.getElementById('add-Coal')
const removeCoal = document.getElementById('remove-Coal')
let coal= displayCoal.innerHTML/1;
let coalEl=25;
let coalCo2=45;
let coalCost=100;
let coalsell=65;

const addOil = document.getElementById('add-Oil')
const removeOil = document.getElementById('remove-Oil')
let oil=displayOil.innerHTML/1;
let oilEl=20;
let oilCo2=35;
let oilCost=150;
let oilsell=100;

const addNaturalGas = document.getElementById('add-NaturalGas')
const removeNaturalGas = document.getElementById('remove-NaturalGas')
let naturalGas=displayNaturalGas.innerHTML/1;
let naturalGasEl=15;
let naturalGasCo2=25;
let naturalGasCost=200;
let naturalGassell=70;

const addWind = document.getElementById('add-Wind')
const removeWind = document.getElementById('remove-Wind')
let wind=displayWind.innerHTML/1;
let windEl=15;
let windCo2=2;
let windCost=300;
let windsell=100;

const addSolar = document.getElementById('add-Solar')
const removeSolar = document.getElementById('remove-Solar')
let solar=displaySolar.innerHTML/1;
let solarEl=10;
let solarCo2=1;
let solarCost=250;
let solarsell=85;

const addHydroelectric = document.getElementById('add-Hydroelectric')
const removeHydroelectric = document.getElementById('remove-Hydroelectric')
let hydroelectric=displayHydroelectric.innerHTML/1;
let hydroelectricEl=20;
let hydroelectricCo2=3;
let hydroelectricCost=350;
let hydroelectricsell=120;
//--------------------------------------****EventListener for factories****-------------------------------------------
addCoal.addEventListener('click',increaseNumberOfCoalFactory)
removeCoal.addEventListener('click',decreaseNumberOfCoalFactory)
//-------------------------------------------
addOil.addEventListener('click',increaseNumberOfOilFactory)
removeOil.addEventListener('click',decreaseNumberOfOilFactory)
//-------------------------------------------
addNaturalGas.addEventListener('click',increaseNumberOfNaturalGasFactory)
removeNaturalGas.addEventListener('click',decreaseNumberOfNaturalGasFactory)
//-------------------------------------------
addWind.addEventListener('click',increaseNumberOfWindFactory)
removeWind.addEventListener('click',decreaseNumberOfWindFactory)
//-------------------------------------------
addSolar.addEventListener('click',increaseNumberOfSolarFactory)
removeSolar.addEventListener('click',decreaseNumberOfSolarFactory)
//-------------------------------------------
addHydroelectric.addEventListener('click',increaseNumberOfHydroelectricFactory)
removeHydroelectric.addEventListener('click',decreaseNumberOfHydroelectricFactory)
//--------------------------------------****Increase and Decrease number of factories****-------------------------------------------
function increaseNumberOfCoalFactory(){
    if(money>coalCost){
        coal +=1;
        removeCoal.disabled = false;
        money -=coalCost
    }else{
        alert('not enough money')
    }
    displayNumber(displayCoal, coal)
}
function decreaseNumberOfCoalFactory(){
    coal -=1;
    money +=coalsell
    if(coal < 1){removeCoal.disabled = true;}
    displayNumber(displayCoal, coal);
}
//-------------------------------------------
function increaseNumberOfOilFactory(){
    if(money>oilCost){
        oil+=1;
        removeOil.disabled = false;
        money -=oilCost
    }else{
        alert('not enough money')
    }
    displayNumber(displayOil, oil)
}
function decreaseNumberOfOilFactory(){
    oil -=1;
    money +=oilsell
    if(oil < 1){removeOil.disabled = true;}
    displayNumber(displayOil, oil);
}
//-------------------------------------------
function increaseNumberOfNaturalGasFactory(){
    if(money>naturalGasCost){
        naturalGas +=1;
        removeNaturalGas.disabled = false;
       money -=naturalGasCost
    }else{
       alert('not enough money')
    }
    displayNumber(displayNaturalGas, naturalGas)
}
function decreaseNumberOfNaturalGasFactory(){
    naturalGas -=1;
    money += naturalGassell
    if(naturalGas < 1){removeNaturalGas.disabled = true;}
    displayNumber(displayNaturalGas, naturalGas);
}
//-------------------------------------------
function increaseNumberOfWindFactory(){
    if(money>windCost){
        wind +=1;
        removeWind.disabled = false;
        money -=windCost
    }else{
        alert('not enough money')
    }
    displayNumber(displayWind, wind)
}
function decreaseNumberOfWindFactory(){
    wind -=1;
    money += windsell
    if(wind < 1){removeWind.disabled = true;}
    displayNumber(displayWind, wind);
}
//-------------------------------------------
function increaseNumberOfSolarFactory(){
    if(money>solarCost){
        solar +=1;
        removeSolar.disabled = false;
        money -=solarCost
    }else{
       alert('not enough money')
    }
    displayNumber(displaySolar, solar)
}
function decreaseNumberOfSolarFactory(){
    solar -=1;
    money += solarsell
    if(solar < 1){removeSolar.disabled = true;}
    displayNumber(displaySolar, solar);
}
//-------------------------------------------
function increaseNumberOfHydroelectricFactory(){
    if(money>hydroelectricCost){
        hydroelectric +=1;
        removeHydroelectric.disabled = false;
       money -=hydroelectricCost
    }else{
       alert('not enough money')
    }
    displayNumber(displayHydroelectric, hydroelectric)
}
function decreaseNumberOfHydroelectricFactory(){
    hydroelectric -=1;
    money += hydroelectricsell
    if(hydroelectric < 1){removeHydroelectric.disabled = true;}
    displayNumber(displayHydroelectric, hydroelectric);
}
//-------------------------------------------
function displayNumber(element, item){
    element.innerHTML = item;
}
//--------------------------------------****Game Calculations****-------------------------------------------
var elSum=1;//Decleration for the amount of electricity
var co2Sum=1;//Decleration for the amount of CO2
var temp = 0;
var population= 300; //Decleration for the starting population number
var money=150; //Decleration for the starting money amount
function electrecitySum(){
    elSum = coalEl*coal + oilEl*oil + naturalGasEl*naturalGas + windEl*wind + solarEl*solar + hydroelectricEl*hydroelectric - population;
    return elSum;//amount of electricity
}
function co2_Sum(){
    co2Sum = coalCo2*coal + oilCo2*oil + naturalGasCo2*naturalGas + windCo2*wind + solarCo2*solar + hydroelectricCo2*hydroelectric - 50;
    temp += co2Sum/850 //amount of CO2
    return temp; 
}
function consumption(){
    population *= 1.005;//population growth speed
    displayPopulation.innerHTML = Math.round(population);
}
function economy(){
    money = money*1.02 //economy growth speed
    displayMoney.innerHTML =Math.round(money)
}
//--------------------------------------****Game functions****-------------------------------------------
startButton.addEventListener('click',run)

var isRunning = true;
var x;

function run(){ 
    menu.classList.add('hide')
    allGameElements.classList.remove('hide')
    getX()
    getY()
    move()
}

function getX(){
    x = setInterval(function slow(){
        consumption()
        economy()
        electrecitySum()
        co2_Sum()
        if(Math.round(electrecitySum()) < 0){
            lost("you ran out of electrecity")
        }else if(co2_Sum() > 10000){
            lost("Too much CO2")
        }
        if(coal==0&&oil==0&&naturalGas==0){
            win()
        }
    },500);
}
function getY(){
    var y =setInterval(function fast(){
        displayElSum.innerHTML=Math.round(electrecitySum());
        displayCo2Sum.innerHTML=Math.round(co2_Sum());
        if(!isRunning){
            clearInterval(y)
        }
    },500);
}

function lost(text){
    clearInterval(x)
    isRunning = false;
    console.log("stop")
    allGameElements.classList.add('hide')
    loseElement.classList.remove('hide')
    whyLost.innerHTML = text;
}
function win(){
    clearInterval(x)
    isRunning = false;
    allGameElements.classList.add('hide')
    winElement.classList.remove('hide')
}

restartButtonLose.addEventListener('click', redos)
restartButtonWin.addEventListener('click', redos)
function redos(){location.reload()}

//--------------------------------------****Information Menu****-------------------------------------------
informationButton.addEventListener('click', information)
backButton.addEventListener('click', goBack1)

function information(){
    infoDisplay.classList.remove('hide')
    controllers.classList.add('hide')
}
function goBack1(){
    infoDisplay.classList.add('hide')
    controllers.classList.remove('hide')
}
//--------------------------------------****Charts/bars****-------------------------------------------
function move() {  
    var elProcent = electrecitySum();
    var id = setInterval(elFrame, 1);
    function elFrame() {
        elProcent = electrecitySum();
        if (elProcent >= 1000) {
            clearInterval(id);
        }else {
            elStatus.style.height = elProcent/10 + '%';
        }
        
        if(elProcent <= 200){
            elStatus.style.backgroundColor = "#e22b2b";
        }else if(elProcent > 200){
            elStatus.style.backgroundColor = "#f6bc0f";
        }
    }

    var co2Procent = co2_Sum();
    var id2 = setInterval(co2Frame, 1);
    function co2Frame() {
        co2Procent = co2_Sum();
        if (co2Procent/100 >= 10000) {
            clearInterval(id2);
        }else {
            co2Status.style.height = co2Procent/100 + '%';
        }

        if(co2Procent >= 8000){
            co2Status.style.backgroundColor = "#e22b2b";
        }else if(co2Procent < 8000){
            co2Status.style.backgroundColor = "#20e039";
        }
    }

    setInterval(rerun,1)
    function rerun(){
        if(elProcent< 1000){
            setInterval(elFrame, 1)
        }else if(co2Procent/100< 10000){
            setInterval(co2Frame, 1)
        }
    }
    
}