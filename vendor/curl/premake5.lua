project "libcurl"
	configurations { "Debug", "Release" }
	objdir "../../build/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}/obj"
    targetdir "../../build/%{cfg.platform}/%{cfg.buildcfg}/%{prj.name}/bin"
	language    "C"
	kind        "StaticLib"
	includedirs { "lib", "include" }
	warnings    "off"

	files {
		"**.h",
		"**.c"
	}

	vpaths {
		["Headers"] = "**.h",
		["Sources/*"] = "**.c"
	 }

	filter "configurations:Debug"
      defines { "_DEBUG", "BUILDING_LIBCURL", "DEBUGBUILD", "CURL_STATICLIB", "USE_IPV6" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG", "BUILDING_LIBCURL", "CURL_STATICLIB", "USE_IPV6" }
      optimize "Speed"

	filter { "system:windows" }
		defines { "USE_SCHANNEL", "USE_WINDOWS_SSPI" }
		links "crypt32"

	filter { "system:macosx" }
		defines { "USE_DARWINSSL" }

	filter { "system:not windows", "system:not macosx" }
		defines { "USE_MBEDTLS" }

	filter { "system:linux or bsd or solaris" }
		defines { "CURL_HIDDEN_SYMBOLS" }

		-- find the location of the ca bundle
		local ca = nil
		for _, f in ipairs {
			"/etc/ssl/certs/ca-certificates.crt",
			"/etc/pki/tls/certs/ca-bundle.crt",
			"/usr/share/ssl/certs/ca-bundle.crt",
			"/usr/local/share/certs/ca-root.crt",
			"/usr/local/share/certs/ca-root-nss.crt",
			"/etc/certs/ca-certificates.crt",
			"/etc/ssl/cert.pem" } do
			if os.isfile(f) then
				ca = f
				break
			end
		end
		if ca then
			defines { 'CURL_CA_BUNDLE="' .. ca .. '"' }
		end
