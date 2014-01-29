//
//  ZepViewController.m
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#include "Zep/Game.h"
#import "Zep-iOS/View.h"
#import "Zep-iOS/ViewController.h"

@implementation ZepViewController

- (id)initWithGame:(Zep::Game*)aGame
{
    game = aGame;
    return [self initWithNibName:nil bundle:nil];
}

- (void)loadView
{
    Zep::TouchSurface& touchSurface = game->getTouchSurface();
    Zep::Screen& screen = game->getScreen();
    ZepView *view = [[ZepView alloc] initWithZepScreen:screen ZepTouchSurface:touchSurface];
    self.view = view;
    //game->getScreen()->setView(view);
}

- (void)run
{
    game->initialize();
    CADisplayLink *displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(tick:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (void)tick:(CADisplayLink *)displayLink
{
    game->update(displayLink.duration);
}

- (BOOL)prefersStatusBarHidden
{
    return YES;
}

@end
