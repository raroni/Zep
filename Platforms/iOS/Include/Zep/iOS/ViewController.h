//
//  ZepViewController.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#import <UIKit/UIKit.h>

namespace Zep {
    class Game;
}

@interface ZepViewController : UIViewController
{
    Zep::Game* game;
}
- (id)initWithGame:(Zep::Game*)aGame;
- (void)run;
@end
