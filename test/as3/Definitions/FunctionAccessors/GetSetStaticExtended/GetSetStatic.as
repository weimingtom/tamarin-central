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

package GetSetStaticExtended {

	
   	internal class GetSetStaticInternal {
	
		private static var _nt = "no type";
		private static var _x:Array = [1,2,3];
		private static var _y:int = -10;
		private static var _b:Boolean = true;
		private static var _u:uint = 1;
		private static var _s:String = "myString";

		private var _n:Number = 555;

		public static function get n():Number {
			return _n;
		}

		public static function set n(num):void {
			_n = num;
		}

		public static function get x():Array {
			return _x;
		}
		public static function set x( a:Array ) {
			_x=a;
		}
		public static function get y():int {
			return _y;
		}
		public static function set y( i:int ) {
			_y=i;
		}
		public static function get boolean():Boolean { return _b; }
		public static function set boolean(b:Boolean) { _b=b; }
		public static function get u():uint{ return _u; }
		public static function set u(ui:uint) { _u=ui; }
		public static function get string():String{ return _s; }
		public static function set string(s:String) { _s=s; }
		public static function get noType():String{ return _s; }
		public static function set noType(nt) { _nt=nt; }

			
	}
        public class GetSetStatic extends GetSetStaticInternal {
	  
	  
   	}

}
