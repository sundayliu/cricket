/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package net.tatamobile.cricket;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;

public class Cricket extends Cocos2dxActivity{
    
    public static SharedPreferences sharedPreferences;
    public static SharedPreferences.Editor editor;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
	      sharedPreferences = this.getSharedPreferences("cricket",Context.MODE_PRIVATE);
	      editor = sharedPreferences.edit();
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// Cricket should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    
    public static void saveBool(String key, boolean value)
    {
         try
         {
             //SharedPreferences.Editor editor = sharedPreferences.edit();
             editor.putBoolean(key,value);
             editor.commit();
         }
         catch (Exception e)
         {
             return;
         }
    }
    public static boolean getBool(String key, boolean defValue)
    {
         try
         {
               boolean v = sharedPreferences.getBoolean(key, defValue);
               return v;
         }
         catch (Exception e)
         {
              return false;
         }
    }
    public static void saveInt(String key, int value)
    {
         try
         {
             //SharedPreferences.Editor editor = sharedPreferences.edit();
             editor.putInt(key,value);
             editor.commit();
         }
         catch (Exception e)
         {
             return;
         }
    }
    public static int getInt(String key, int defValue)
    {
         try
         {
               int v = sharedPreferences.getInt(key, defValue);
               return v;
         }
         catch (Exception e)
         {
              return -1000;
         }
    }
    
    //保存数组的方法
    public static void saveIntArr(String key,int[] value,int ROW,int COL)
    {
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putInt(key+i+j,value[i*COL+j]);
                editor.commit();
            }
        }
    }
    
    //得到数组的方法
    public static int[] getIntArr(String key,int ROW,int COL)
    {
        int arr[] = new int[ROW*COL];
        for(int i=0;i<ROW;i++)
        {
            for(int j=0;j<COL;j++)
            {
                arr[i*COL+j] = sharedPreferences.getInt(key+i+j, -1000);
            }
        }
        return arr;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
