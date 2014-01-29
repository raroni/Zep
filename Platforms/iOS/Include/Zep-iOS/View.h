//
//  ZepView.h
//  Zep
//
//  Created by Rasmus Rønn Nielsen on 28/01/14.
//  Copyright (c) 2014 Tickleworks. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "Zep-iOS/TouchIDHelper.h"

namespace Zep {
    class Screen;
    class TouchSurface;
}

@interface ZepView : UIView
{
    Zep::Screen *zepScreen;
    Zep::TouchSurface *zepTouchSurface;
    Zep::TouchIDHelper *touchIDHelper;
    EAGLContext *context;
    GLuint colorRenderbufferHandle;
    GLuint depthRenderbufferHandle;
}
- (id)initWithZepScreen:(Zep::Screen&)screen ZepTouchSurface:(Zep::TouchSurface&)touchSurface;
- (void)setupFrameBuffer;
- (void)present;
- (void)dealloc;
@end
