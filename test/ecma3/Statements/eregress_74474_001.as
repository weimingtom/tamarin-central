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
/*
* The contents of this file are subject to the Netscape Public
* License Version 1.1 (the "License"); you may not use this file
* except in compliance with the License. You may obtain a copy of
* the License at http://www.mozilla.org/NPL/
*
* Software distributed under the License is distributed on an "AS IS" 
* basis, WITHOUT WARRANTY OF ANY KIND, either expressed
* or implied. See the License for the specific language governing
* rights and limitations under the License.
*
* The Original Code is mozilla.org code.
*
* The Initial Developer of the Original Code is Netscape
* Communications Corporation.  Portions created by Netscape are
* Copyright (C) 1998 Netscape Communications Corporation. All
* Rights Reserved.
*
* Contributor(s): pschwartau@netscape.com
* Date: 01 May 2001
*
* SUMMARY: Regression test for Bugzilla bug 74474
*"switch() misbehaves with duplicated labels"
*
* See ECMA3  Section 12.11,  "The switch Statement"
* See http://bugzilla.mozilla.org/show_bug.cgi?id=74474
*/
//-------------------------------------------------------------------------------------------------
    var SECTION = "eregress_74474_001";
    var VERSION = "";
    var TITLE   = "Testing switch statements with duplicate labels";
    var bug = 74474;

    startTest();
    writeHeaderToLog( SECTION + " "+ TITLE);

    var testcases = getTestCases();
    
    test();
    
function getTestCases() {
    var array = new Array();
    var item = 0;
        
    var UBound = 0;
    var summary = 'Testing switch statements with duplicate labels';
    var status = '';
    var statusitems = [ ];
    var actual = '';
    var actualvalues = [ ];
    var expect= '';
    var expectedvalues = [ ];


    status = 'Section A of test: the string literal "1" as a duplicate label';
    actual = '';
    switch ('1')
    {
      case '1':
        actual += 'a';
      case '1':
        actual += 'b';
    }
    expect = 'ab';
    //addThis();
    array[item++] = new TestCase(SECTION, status, expect, actual);


    status = 'Section B of test: the numeric literal 1 as a duplicate label';
    actual = '';
    switch (1)
    {
      case 1:
        actual += 'a';
      case 1:
        actual += 'b';
    }
    expect = 'ab';
    //addThis();
    array[item++] = new TestCase(SECTION, status, expect, actual);


    status = 'Section C of test: the numeric literal 1 as a duplicate label, via a function parameter';
    tryThis(1);
    function tryThis(x)
    {
      actual = '';
    
      switch (x)
      {
        case x:
          actual += 'a';
        case x:
          actual += 'b';
      }
    }
    expect = 'ab';
    //addThis();
    array[item++] = new TestCase(SECTION, status, expect, actual);

    return array;
}

/*
function addThis()
{
  statusitems[UBound] = status;
  actualvalues[UBound] = actual;
  expectedvalues[UBound] = expect;
  UBound++;
}
*/

/*

function test()
{
  enterFunc ('test');
  printBugNumber (bug);
  printStatus (summary);
 
  for (var i = 0; i < UBound; i++)
  {
    reportCompare(expectedvalues[i], actualvalues[i], getStatus(i));
  }

  exitFunc ('test');
}
*/

function getStatus(i)
{
  return statusitems[i];
}
