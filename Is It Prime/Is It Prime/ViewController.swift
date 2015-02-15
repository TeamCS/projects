//
//  ViewController.swift
//  Is It Prime
//
//  Created by Boran Liu on 12/27/14.
//  Copyright (c) 2014 KKevinLL. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet var Input: UITextField!
    
    
    @IBAction func Guess(sender: AnyObject) {
        
        var numberInt = Input.text.toInt()
        
        if numberInt != nil
        {
            var unwrapNumber = numberInt!
            
            var isPrime = true
            
            if unwrapNumber == 1
            {
                isPrime = false
            }
            
            if unwrapNumber != 2 && unwrapNumber != 1
            {
                for var i = 2; i < unwrapNumber; i++
                {
                    if unwrapNumber % i == 0
                    {
                        isPrime = false
                    }
                }
            }
            
            if isPrime == true
            {
                answer.text = "\(unwrapNumber) is Prime!"
            }
            else
            {
                answer.text = "\(unwrapNumber) is not Prime!"
            }
        }
        else
        {
            answer.text = "Please enter a number in the box"
        }
    }
    
    @IBOutlet var answer: UILabel!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

