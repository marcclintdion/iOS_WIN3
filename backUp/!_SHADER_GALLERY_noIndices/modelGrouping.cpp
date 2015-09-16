        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);    
        Translate(modelView, flowerShield_POSITION[0], flowerShield_POSITION[1], flowerShield_POSITION[2]);                                                                                         
        Rotate(modelView, flowerShield_ROTATE[0], flowerShield_ROTATE[1], flowerShield_ROTATE[2], flowerShield_ROTATE[3]+spinModel);         
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);         
        Translate(modelView, sculptris_POSITION[0], sculptris_POSITION[1], sculptris_POSITION[2]);                                                                                         
        Rotate(modelView, sculptris_ROTATE[0], sculptris_ROTATE[1], sculptris_ROTATE[2], sculptris_ROTATE[3]+spinModel);         
        #include "_MODEL_FOLDERS_/sculptris/sculptris_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);           
        Translate(modelView, sphere_POSITION[0], sphere_POSITION[1], sphere_POSITION[2]);                                                                                         
        Rotate(modelView, sphere_ROTATE[0], sphere_ROTATE[1], sphere_ROTATE[2], sphere_ROTATE[3] + spinModel);          
        #include "_MODEL_FOLDERS_/sphere/sphere_Render.cpp"  
        //------------------------------------------------------------------------------------                                           
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);           
        Rotate(modelView, 0.0, 0.0, 1.0, 90.0);
        Translate(modelView, spiralGear_POSITION[0], spiralGear_POSITION[1], spiralGear_POSITION[2]);                                                                                         
        Rotate(modelView, spiralGear_ROTATE[0], spiralGear_ROTATE[1], spiralGear_ROTATE[2], spiralGear_ROTATE[3]);        
        #include "_MODEL_FOLDERS_/spiralGear/spiralGear_Render.cpp"          
        //------------------------------------------------------------------------------------                                          
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);           
        Translate(modelView, knight_POSITION[0], knight_POSITION[1], knight_POSITION[2]);                                                                                         
        Rotate(modelView, knight_ROTATE[0], knight_ROTATE[1], knight_ROTATE[2], knight_ROTATE[3]);        
        #include "_MODEL_FOLDERS_/knight/knight_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------    
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);           
        Translate(modelView, torus_POSITION[0], torus_POSITION[1], torus_POSITION[2]);                                                                                         
        Rotate(modelView, torus_ROTATE[0], torus_ROTATE[1], torus_ROTATE[2], torus_ROTATE[3] + spinModel);        
        #include "_MODEL_FOLDERS_/torus/torus_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------   
        LoadIdentity(modelView);                                                                                                                                                  
        Translate(modelView, select_POSITION[0], select_POSITION[1], select_POSITION[2]);           
        Translate(modelView, capsule_POSITION[0], capsule_POSITION[1], capsule_POSITION[2]);                                                                                         
        Rotate(modelView, capsule_ROTATE[0], capsule_ROTATE[1], capsule_ROTATE[2], capsule_ROTATE[3] + spinModel);         
        #include "_MODEL_FOLDERS_/capsule/capsule_Render.cpp"                                                                 
        //------------------------------------------------------------------------------------            
