/* ***** BEGIN LICENSE BLOCK ***** 
 Version: MPL 1.1/GPL 2.0/LGPL 2.1 

The contents of this file are subject to the Mozilla Public License Version 1.1 (the 
"License"); you may not use this file except in compliance with the License. You may obtain 
a copy of the License at http://www.mozilla.org/MPL/ 

Software distributed under the License is distributed on an "AS IS" basis, WITHOUT 
WARRANTY OF ANY KIND, either express or implied. See the License for the specific 
language governing rights and limitations under the License. 

The Original Code is [Open Source Virtual Machine.] 

The Initial Developer of the Original Code is Adobe System Incorporated.  Portions created 
by the Initial Developer are Copyright (C)[ 2005-2006 ] Adobe Systems Incorporated. All Rights 
Reserved. 

Contributor(s): Adobe AS3 Team

Alternatively, the contents of this file may be used under the terms of either the GNU 
General Public License Version 2 or later (the "GPL"), or the GNU Lesser General Public 
License Version 2.1 or later (the "LGPL"), in which case the provisions of the GPL or the 
LGPL are applicable instead of those above. If you wish to allow use of your version of this 
file only under the terms of either the GPL or the LGPL, and not to allow others to use your 
version of this file under the terms of the MPL, indicate your decision by deleting provisions 
above and replace them with the notice and other provisions required by the GPL or the 
LGPL. If you do not delete the provisions above, a recipient may use your version of this file 
under the terms of any one of the MPL, the GPL or the LGPL. 

 ***** END LICENSE BLOCK ***** */
    var SECTION = "15.8.2.3";
    var VERSION = "ECMA_1";
    startTest();
    var TITLE   = "Math.asin()";

    writeHeaderToLog( SECTION + " "+ TITLE);

    var testcases = getTestCases();
    test();

function getTestCases() {
    var array = new Array();
    var item = 0;
 /* var thisError="no error";
    try{
        Math.asin();
    }catch(e:Error){
        thisError=(e.toString()).substring(0,26);
    }finally{//print(thisError);
        array[item++] = new TestCase( SECTION,   "Math.asin()","ArgumentError: Error #1063",thisError);
    }
    array[item++] = new TestCase( SECTION, "Math.asin()",           Number.NaN,     Math.asin() );*/
    array[item++] = new TestCase( SECTION, "Math.asin(void 0)",     Number.NaN,     Math.asin(void 0) );
    array[item++] = new TestCase( SECTION, "Math.asin(null)",       0,              Math.asin(null) );
    array[item++] = new TestCase( SECTION, "Math.asin(NaN)",        Number.NaN,     Math.asin(Number.NaN)   );

    array[item++] = new TestCase( SECTION, "Math.asin('string')",   Number.NaN,     Math.asin("string")     );
    array[item++] = new TestCase( SECTION, "Math.asin('0')",        0,              Math.asin("0") );
    array[item++] = new TestCase( SECTION, "Math.asin('1')",        Math.PI/2,      Math.asin("1") );
    array[item++] = new TestCase( SECTION, "Math.asin('-1')",       -Math.PI/2,     Math.asin("-1") );
    array[item++] = new TestCase( SECTION, "Math.asin(Math.SQRT1_2+'')",    0.7853981633974484,  Math.asin(Math.SQRT1_2+'') );
    array[item++] = new TestCase( SECTION, "Math.asin(-Math.SQRT1_2+'')",   -0.7853981633974484, Math.asin(-Math.SQRT1_2+'') );

    array[item++] = new TestCase( SECTION, "Math.asin(1.000001)",    Number.NaN,    Math.asin(1.000001)     );
    array[item++] = new TestCase( SECTION, "Math.asin(-1.000001)",   Number.NaN,    Math.asin(-1.000001)    );
    array[item++] = new TestCase( SECTION, "Math.asin(0)",           0,             Math.asin(0)            );
    array[item++] = new TestCase( SECTION, "Math.asin(-0)",          -0,            Math.asin(-0)           );

    array[item++] = new TestCase( SECTION, "Infinity/Math.asin(-0)",    -Infinity,  Infinity/Math.asin(-0) );

    array[item++] = new TestCase( SECTION, "Math.asin(1)",              Math.PI/2,  Math.asin(1)            );
    array[item++] = new TestCase( SECTION, "Math.asin(-1)",             -Math.PI/2, Math.asin(-1)            );
    array[item++] = new TestCase( SECTION, "Math.asin(Math.SQRT1_2))",  0.7853981633974484,  Math.asin(Math.SQRT1_2) );
    array[item++] = new TestCase( SECTION, "Math.asin(-Math.SQRT1_2))", -0.7853981633974484, Math.asin(-Math.SQRT1_2));

    return ( array );
}
