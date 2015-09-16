(function () {
	var CR_GR_LIGHT_URL		= 'http://cdn.assets.craveonline.com/comscore_branding/logos/gr_white.png';
	var CR_GR_DARK_URL		= 'http://cdn.assets.craveonline.com/comscore_branding/logos/gr_white.png';
	var CR_GR     = "CR_GR";
	var CR_NA	  = "NonTH";
    
	var CR_GR_SITES     = [ 
        'n4g', 'siliconera', 'actiontrip', 'xbox360achievements', 'ps3trophies', 'cheathappens', 'vgreleases', 'xbox-scene', 'gamerevolution', 'moddb', 'gamewinners', 'destructoid', 'chaptercheats', 'strategywiki', 'zeldadungeon', 'segmentnext', 'gamingbolt', 'cheatmasters', 'rpg', 'gamepressure', 'gamebanana', 'psu', 'psxextreme', 'megagames', 'trueachievements', 'beefjack', 'eventhubs', 'zeldauniverse', 'playstationlifestyle', 'justpushstart', 'blisteredthumbs', 'thebitbag', 'indiedb', 'ripten', 'zeldainforner', 'gameanyone', 'nintendoeverything', 'gamingeverything', 'gamereplays', 'wiinintendo', 'wiichat', 'iplaywinner', 'cheatingdome', 'gamekicker', 'pspcrazy', 'wiisworld', 'gamerlimit', 'gamersmint', 'pspworld', 'totalgamingnetwork', 'kokugamer', 'qj', 'psx-scene', 'psxhax', 'dashhacks', 'gamedynamo', 'gamesntrailers', 'rpgamer', 'angryjoeshow', 'epicbattleaxe', 'gamrreview', 'ps3chat', 'screwattack', 'wegotthiscovered', 'xboxlivenation', 'zeldainformer', 'darksidersdungeon', 'gengame'
    ];
    
    var domain = getRootURL(document.domain);
	var brand = searchDomain(domain);
    
	var queryObj = parseQuery();
	
	var useDark;
	if( typeof queryObj.useDarkLogo != 'undefined' && queryObj.useDarkLogo.match(/false/i) ) {
		useDark = false;
	}
	else {
		useDark = true;
	}
	
	printBranding( brand, useDark )
	
	//******** FUNCTIONS **********//
	function getRootURL(url){
		var TLDs = ['ac', 'ad', 'ae', 'aero', 'af', 'ag', 'ai', 'al', 'am', 'an', 'ao', 'aq', 'ar', 'arpa', 'as', 'asia', 'at', 'au', 'aw', 'ax', 'az', 'ba', 'bb', 'bd', 'be', 'bf', 'bg', 'bh', 'bi', 'biz', 'bj', 'bm', 'bn', 'bo', 'br', 'bs', 'bt', 'bv', 'bw', 'by', 'bz', 'ca', 'cat', 'cc', 'cd', 'cf', 'cg', 'ch', 'ci', 'ck', 'cl', 'cm', 'cn', 'co', 'com', 'coop', 'cr', 'cu', 'cv', 'cx', 'cy', 'cz', 'de', 'dj', 'dk', 'dm', 'do', 'dz', 'ec', 'edu', 'ee', 'eg', 'er', 'es', 'et', 'eu', 'fi', 'fj', 'fk', 'fm', 'fo', 'fr', 'ga', 'gb', 'gd', 'ge', 'gf', 'gg', 'gh', 'gi', 'gl', 'gm', 'gn', 'gov', 'gp', 'gq', 'gr', 'gs', 'gt', 'gu', 'gw', 'gy', 'hk', 'hm', 'hn', 'hr', 'ht', 'hu', 'id', 'ie', 'il', 'im', 'in', 'info', 'int', 'io', 'iq', 'ir', 'is', 'it', 'je', 'jm', 'jo', 'jobs', 'jp', 'ke', 'kg', 'kh', 'ki', 'km', 'kn', 'kp', 'kr', 'kw', 'ky', 'kz', 'la', 'lb', 'lc', 'li', 'lk', 'lr', 'ls', 'lt', 'lu', 'lv', 'ly', 'ma', 'mc', 'md', 'me', 'mg', 'mh', 'mil', 'mk', 'ml', 'mm', 'mn', 'mo', 'mobi', 'mp', 'mq', 'mr', 'ms', 'mt', 'mu', 'museum', 'mv', 'mw', 'mx', 'my', 'mz', 'na', 'name', 'nc', 'ne', 'net', 'nf', 'ng', 'ni', 'nl', 'no', 'np', 'nr', 'nu', 'nz', 'om', 'org', 'pa', 'pe', 'pf', 'pg', 'ph', 'pk', 'pl', 'pm', 'pn', 'pr', 'pro', 'ps', 'pt', 'pw', 'py', 'qa', 're', 'ro', 'rs', 'ru', 'rw', 'sa', 'sb', 'sc', 'sd', 'se', 'sg', 'sh', 'si', 'sj', 'sk', 'sl', 'sm', 'sn', 'so', 'sr', 'st', 'su', 'sv', 'sy', 'sz', 'tc', 'td', 'tel', 'tf', 'tg', 'th', 'tj', 'tk', 'tl', 'tm', 'tn', 'to', 'tp', 'tr', 'travel', 'tt', 'tv', 'tw', 'tz', 'ua', 'ug', 'uk', 'us', 'uy', 'uz', 'va', 'vc', 've', 'vg', 'vi', 'vn', 'vu', 'wf', 'ws', 'xxx', 'ye', 'yt', 'za', 'zm', 'zw'].join()

		var parts = url.split('.');
		if (parts[0] === 'www' && parts[1] !== 'com'){
			parts.shift()
		}
		var ln = parts.length
		  , i = ln
		  , minLength = parts[parts.length-1].length
		  , part

		// iterate backwards
		while(part = parts[--i]){
			if (i === 0                    
				|| i < ln-2                
				|| part.length < minLength 
				|| TLDs.indexOf(part) < 0  
			){
				return part
			}
		}
	}
	
    function searchDomain(domain) {
	
		var GRi = CR_GR_SITES.length;
		
		while (GRi--) {
		   if (CR_GR_SITES[GRi] === domain) {
			   return "CR_GR";
		   }
		}
		
		
		return "NonTH";
		
	}
	
	function printBranding( brand, useDark )
	{
		
		var outImgStr = "<img src='";
		
		switch( brand )
		{
			case CR_GR:
				if( useDark ) {
					outImgStr += CR_GR_DARK_URL;
				}
				else {
					outImgStr += CR_GR_LIGHT_URL;
				}
				break;
				
				
			default:
				break;
		}
		
		outImgStr += "' alt='Crave Online' width='194px' height='20px' />";
		
		if(brand != "NonTH")
		{ 
			document.write( outImgStr );
		}
	}
    
    function parseQuery (  ) 
    {
        var scripts = document.getElementsByTagName('script');
        var myScript = scripts[ scripts.length - 1 ];
		var query = myScript.src.replace(/^[^\?]+\??/,'');
		
        var Params = new Object ();
       
        if ( ! query ) return Params; // return empty object
        var Pairs = query.split(/[;&]/);
        for ( var i = 0; i < Pairs.length; i++ ) 
        {
            var KeyVal = Pairs[i].split('=');
            if ( ! KeyVal || KeyVal.length != 2 ) continue;
            var key = unescape( KeyVal[0] );
            var val = unescape( KeyVal[1] );
            val = val.replace(/\+/g, ' ');
            Params[key] = val;
		}
		return Params;
    }
})();