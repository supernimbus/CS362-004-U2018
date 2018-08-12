

import java.util.Random;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

import org.junit.Assert;
import org.junit.Test;




public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }
   public void testIsValid() {
	   System.out.println("Hello world!!!!");
	   testIsValid(UrlValidator.ALLOW_ALL_SCHEMES);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   
   //simplified version of testisValid
   public void testIsValid(long allowAllSchemes)
   {
	boolean expectedResult = true;
	//boolean output;
	Random rand = new Random();
	int randomIndex;
	StringBuilder testBuffer = new StringBuilder();
	UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	String url;    //url being tested
	
	//hold one thing constant at a time...
	//case1: fully valid url
	assertTrue(urlVal.isValid("http://www.google.com"));
	
	//case2: invalid urlScheme
	assertFalse(urlVal.isValid("http/www.google.com"));
	
	//case3: invalid test body
	urlVal.isValid("http:/900.900.900.900");
	assertFalse(urlVal.isValid("http:/900.900.900.900"));
	//output = urlVal.isValid("http:/900.900.900.900");
	//assertEquals("what", false, output);
	
	//case4: invalid test port
	assertFalse(urlVal.isValid("http://www.google.com:-1"));
	
	//case5: invalid test path
	assertFalse(urlVal.isValid("http://www.google.com/#"));
	
	//case6: valid query
	assertTrue(urlVal.isValid("http://www.google.com/?action=view"));
	
	
	//try different random combinations
	//based on the original "testIsValid()" function
	
	expectedResult = true;
	for (int i = 0; i < 4000; i++) {
		//reset buffer
		testBuffer.setLength(0);
		
		expectedResult = true;
		randomIndex = rand.nextInt(5);
		testBuffer.append(testUrlScheme[randomIndex].item);
		if (testUrlScheme[randomIndex].valid == false && expectedResult == true) {
			expectedResult = false;
		}
		randomIndex = rand.nextInt(5);
		testBuffer.append(testUrlBody[randomIndex].item);
		if (testUrlBody[randomIndex].valid == false && expectedResult == true) {
			expectedResult = false;
		}
		randomIndex = rand.nextInt(5);
		testBuffer.append(testPort[randomIndex].item);
		if (testPort[randomIndex].valid == false && expectedResult == true) {
			expectedResult = false;
		}
		randomIndex = rand.nextInt(5);
		testBuffer.append(testPath[randomIndex].item);
		if (testPath[randomIndex].valid == false && expectedResult == true) {
			expectedResult = false;
		}
		
		url = testBuffer.toString();
		boolean result = urlVal.isValid(url);
		if (result == true) {
			System.out.println(url);
		}
		assertEquals(url, expectedResult, result);
		
		//test with appended query (queries are valid, so the expected result check is not necessary here)
		randomIndex = rand.nextInt(2);
		testBuffer.append(testUrlQuery[randomIndex].item);
		url = testBuffer.toString();
		result = urlVal.isValid(url);
		assertEquals(url, expectedResult, result);
		
	}
		   

   }
   
   //public static void main(String[] argv) {
//	   System.out.println("we even here dude?");

//	   UrlValidatorTest fct = new UrlValidatorTest("url test");
//	   fct.testIsValid();
//   }
   
   
   
   ResultPair[] testUrlScheme = {new ResultPair("http://", true), 
		   new ResultPair("ftp://", true),
		   new ResultPair("http/", false),
		   new ResultPair("", true),
		   new ResultPair("://", false),
		   new ResultPair("http:", false)};
   
   ResultPair[] testUrlBody = {new ResultPair("google.com", true),
		   new ResultPair("amazon.com", true),
		   new ResultPair("google.com.mx", true),
		   new ResultPair("900.900.900.900", false),
		   new ResultPair("", false),
		   new ResultPair("...lol...", false) };
		   
   ResultPair[] testPort = {new ResultPair(":80", true),
		   new ResultPair(":65535", true),
		   new ResultPair(":abcd", false),
		   new ResultPair("", true),
		   new ResultPair(":-1", false),
		   new ResultPair(":32z", false) };

   ResultPair[] testPath = {new ResultPair("/test1", true),
		   new ResultPair("/123", true),
		   new ResultPair("/../", false),
		   new ResultPair("", true),
		   new ResultPair("/#", false),
		   new ResultPair("/first/second", true)};
   
   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("", true)};

   
   
}









