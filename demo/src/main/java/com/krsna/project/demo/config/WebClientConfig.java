package com.krsna.project.demo.config;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.reactive.function.client.WebClient;

@Configuration
public class WebClientConfig {
    @Value("${cerebras.api.url}")
    private String apiUrl;

    @Value("${cerebras.api.key}")
    private String apiKey;

    @Bean
    public WebClient cerabrasWebClient(){
        return WebClient.builder()
                .baseUrl(apiUrl)
                .defaultHeader("Authorization","Bearer "+apiKey)
                .defaultHeader("Content-Type","application/json")
                .build();
    }

}
