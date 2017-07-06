<!--

// _dom indicates, which DOM we are dealing with. The values are: 
//	1:	W3C / Mozilla / IE5.5 / NS6
//	2:	NS4 / Communicator
//	3:	IE4
var _dom = 0;

// Reference to the form 
var form1;

//	Reference to the hidden field "SUBMITPATTERN"
var submitPattern;

// Reference to the hidden field "RETURNPATTERN"
var returnPattern;

// Reference to the hidden field "ESCAPEPATTERN"
var escapePattern;

// Reference to textfield "C15_Verwendungszweck1"
var reason1;

// Reference to textfield "C15_Verwendungszweck2"
var reason2;

var formRetrieved;

var submitOK;

var pageID;

/* If page contains a form this function will set the focus to the first 
	textfield of that form.*/
function setFocus() {
	if (document.forms.length > 0) {
		var form = document.forms[0]
		var num = form.elements.length;
		for (var i = 0; i < num; i++) {
			if ((form.elements[i].type == "text" 
				|| form.elements[i].type == "textarea" 
				|| form.elements[i].type == "password")
				&& !form.elements[i].disabled) {
				form.elements[i].focus();
				break;
			}
		}
	}
}

function correctFocus() {
	// Check if current form is the transferform.
	// (The transferform has input fields "C15_Verwendungszweck1"
	// and "C15_Verwendungszweck2", which we mapp to "reason1"
	// and "reason2" during init().)
	// First call setFocus() and afterwards
	// correctFocus().
	if ((reason1 != null) && (reason2 != null) && (formRetrieved != null)) {

		if (_dom == 1) {	// Mozilla
			if (formRetrieved.getAttribute("value") == "1") {
				if (reason1.getAttribute("value") == "") {	
					reason1.focus();
				} else if (reason2.getAttribute("value") == "") {
					reason2.focus();
				}
			}
		} else {	// NS4 & IE4
			if(formRetrieved.value == "1") {
				if (reason1.value =="") {
					reason1.focus();
				} else if (reason2.value =="") {
					reason2.focus();
				} 
			}
		}
	}
}
	
			 

/* Initialize references. */
function init()	{

	submitPattern = null;
	escapePattern = null;
	returnPattern = null;

	pageID=null;

	if(document.all)	{
		_dom=3;
	}	else	if(document.getElementById)	{
  		_dom=1;
	}	else	if(document.layers)	{
		_dom=2;	
	}

// alert("Dom = "+_dom);	

	// Event handler when a key goes down
	document.onkeydown = keydownhandler;
	
	// Event handler when a key is held down
	document.onkeypress = keypresshandler;	
	
	// Event handler when a key is held down
	document.onkeyup = keyuphandler;	
	
	// get the references to the form and the hidden parameters we want to use
	if(_dom==1)	{	//Mozilla
		form1 = document.getElementsByTagName("form").item(0);
		inputs = document.getElementsByTagName("input");
		if (inputs != null) {
			for (var i = 0; i<inputs.length; i++)	{

				// First find hidden fields required for 
				// event handling.
				aName=inputs.item(i).getAttribute("name");
				if (aName=="SUBMITPATTERN")	{
					// in case of multiple forms use the first one
					if(submitPattern == null) {
						submitPattern = inputs.item(i);
					}	
				}	
				if (aName=="RETURNPATTERN")	{
					if(returnPattern == null) {
						returnPattern = inputs.item(i);
					}	
				}	
				if (aName=="ESCAPEPATTERN")	{
					if(escapePattern == null) {
						escapePattern = inputs.item(i);
					}	
				}
				
		
				// Now find reason1/reason2 fields:
				if (aName=="C15_Verwendungszweck1")	{
					reason1 = inputs.item(i);
				}	
				if (aName=="C15_Verwendungszweck2")	{
					reason2 = inputs.item(i);
				}	
				if (aName=="FormRetrieved")	{
					formRetrieved = inputs.item(i);
				}						
				
			}
		}
	}	else	if (_dom==2)	{			// NS4
		form1 = document.forms[0];
		if (form1 != null) {
			submitPattern = document.forms[0].SUBMITPATTERN;
			returnPattern = document.forms[0].RETURNPATTERN;
			escapePattern = document.forms[0].ESCAPEPATTERN;
			reason1 = document.forms[0].C15_Verwendungszweck1;
			reason2 = document.forms[0].C15_Verwendungszweck2;
			formRetrieved = document.forms[0].FormRetrieved; 
			pageID = document.forms[0].PAGEID;
		}
		
	}	else	if (_dom==3)	{			// IE4
		form1 = document.forms[0];
		if (form1 != null) {
			submitPattern = document.forms[0].SUBMITPATTERN;
			returnPattern = document.forms[0].RETURNPATTERN;
			escapePattern = document.forms[0].ESCAPEPATTERN;
			reason1 = document.forms[0].C15_Verwendungszweck1;
			reason2 = document.forms[0].C15_Verwendungszweck2;
			formRetrieved = document.forms[0].FormRetrieved; 
		}
		
	}
	
	if (form1 != null) {
		form1.onkeydown = keydownhandler;	
	}

	setFocus();
	correctFocus(); 
		
}

function keypresshandler(evt)	{

	//	keycode as ASCII
	var key;
	// prevent IE from doing its own key event handling.
	//
	// NS ?
	// 
	if (_dom==3)	{			
		evt = window.event;
		key = evt.keyCode;
		if((key == 13)||(key == 27))	{					// "Return", "Escape"
			evt.keyCode=0;
		}
	}

	if(_dom==2)	{
		key = evt.which;
		if((key == 13)||(key == 27))	{					// "Return", "Escape"
			evt.which=0;
		}
	}

}

function keyuphandler(evt)	{
	//	keycode as ASCII
	var key;
	// prevent IE from doing its own key event handling.
	if (_dom==3)	{			
		evt = window.event;
		key = evt.keyCode;
		if((key == 13)||(key == 27))	{					// "Return", "Escape"
			evt.keyCode=0;
		}
	}

	if(_dom==2)	{
		key = evt.which;
		if((key == 13)||(key == 27))	{					// "Return", "Escape"
			evt.which=0;
		}
	}


}
	
/*	Key event handling.	*/
function keydownhandler (evt) {

	//	keycode as ASCII
	var key;
	
	// Catch key event when it bubbles up to the window level for IE4:
	
	if (_dom==3)	{			
		evt = window.event;
	}
	

	// Get keycode for NN4
	if(_dom==2)	{
		key = evt.which;
	}	else {		// get keycode for IE and Mozilla
		key = evt.keyCode;
	}

	// Depending on the key that has been pushed (namely 'return' or 'escape')
	// read out a string from the coresponding hidden field that will become
	// the value of the hidden field SUBMITPATTERN.
	// The field can contain one of the names of the various grafic submit
	// buttons of the form, so the parameter can be evaluated and the 
	// coresponding routine can be invoked after submit even though the button 
	// itself has not been clicked.
	if(key == 13)	{					// "Return"
		var r;
		if(_dom==1)	{					//	Mozilla
			r= returnPattern.getAttribute("value");
			submitPattern.setAttribute("value",r);
		}
		
		if(_dom==2)	{					//	NS4
			if (pageID == null) {
				submitPattern.value=returnPattern.value;
			} else {
				submitPattern.value="";
			}	
			evt.which=0;
		}	
		
		if(_dom==3)	{					//	IE4
			submitPattern.value=returnPattern.value;
			// to prevent IE from generating its own submit.
			evt.keyCode=0;
		}		
		
		if	(submitPattern.value !="")	{
			// just to be on the save side due we 
			// handle this like the escape event, see below.
		 	setTimeout("form1.submit();",100);
		}
	}
	
	if(key == 27)	{					// "Escape"
		if(_dom==1)	{					// Mozilla
			es = escapePattern.getAttribute("value");
			submitPattern.setAttribute("value",es);
		}	
		if(_dom==2)	{					//	NS4
			submitPattern.value=escapePattern.value;
		}	
		
		if(_dom==3)	{					//	IE4
			submitPattern.value=escapePattern.value;
			// to prevent IE from generating a second submit
			evt.keyCode=0;
		}			
				
		if	(submitPattern.value !="")	{
			// otherwise submit gets lost in IE
			setTimeout("form1.submit();",100);
		}	
	}			
}


// Error handling stuff

// Event-Handler setzen

// window.onerror = fehler;

// Array fuer Fehlermeldungen
fehlerText = new Array();
fehlerURL = new Array();
fehlerZeile = new Array();

fehlerNummer = 0;

function fehler(txt, URL, zeile) {

	// Momentan auskommentiert, da es in bestimmten Browsern
	// zu Fehlermeldungen beim Ausführen dieses Codes kommt. (IE)	

	// fehlerText[fehlerNummer] = txt;
	// fehlerURL[fehlerNummer] = URL;
	// fehlerZeile[fehlerNummer] = zeile;
	// fehlerNummer++;

	// Fehlermeldung des Browsers 
	// unterdruecken
	return true;
}


// This function may be called by typing in the URL:
// javascript:ausgabe()
// The JavaScript - errors that have been logged by 
// the function 'fehler' will be displayed in a separate
// window.
function ausgabe() {
	neuesFenster= window.open("", "fehlerAusgabe",
	"scrollbars=yes,width=500,height=400")

	with (neuesFenster.document) {

		open();
		write("<html><head><title>Fehlermeldungen");
		write("</title></head>");

		write("<h1>Folgende Fehler sind aufgetreten:</h1>");

		for (i = 0; i < fehlerNummer; i++) {
			write("<b>Datei:</b> <i>" 
			+ fehlerURL[i] + "</i><br>");
			write("<b>Zeile:</b> <i>" 
			+ fehlerZeile[i] + "</i><br>");
			write("<b>Fehlermeldung:</b> <i>" 
			+ fehlerText[i] + "</i><br><br>");
		}
	
		write("</body></html>");
		close();
	}

}


function open_pb_window(adresse) {
    if (document.layers) window.open(adresse,"produktfenster","innerHeight=500,innerWidth=600,screenX=0,screenY=0,directories=no,location=no,menubar=no,status=yes,toolbar=no,scrollbars=yes");
    else window.open                (adresse,"produktfenster","height=500,     width=600,     left=0,top=0,       directories=no,location=no,menubar=no,status=yes,toolbar=no,scrollbars=yes");
}


// end of error handling functions

// NS4: Capture key - events on document level, because
// they tend to get lost within tables.
if (document.layers) {									
	document.captureEvents(Event.KEYPRESS);
	document.captureEvents(Event.KEYDOWN);
	document.captureEvents(Event.KEYUP);	
}


// -->
