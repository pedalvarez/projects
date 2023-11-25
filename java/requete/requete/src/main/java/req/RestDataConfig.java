package req;

import org.springframework.context.annotation.Configuration;
import org.springframework.data.rest.core.config.RepositoryRestConfiguration;
import org.springframework.data.rest.webmvc.config.RepositoryRestMvcConfiguration;
import org.springframework.http.MediaType;

@Configuration
public class RestDataConfig extends RepositoryRestMvcConfiguration {

    @Override
    public RepositoryRestConfiguration config() {
        RepositoryRestConfiguration config = super.config();
        config.setReturnBodyOnCreate(Boolean.TRUE);
        config.setReturnBodyOnUpdate(Boolean.TRUE);
        config.exposeIdsFor(Req.class);
        config.setDefaultMediaType(MediaType.APPLICATION_JSON);
        return config;
    }
}

