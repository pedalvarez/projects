package req;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.mongodb.repository.config.EnableMongoRepositories;
import org.springframework.data.web.HateoasPageableHandlerMethodArgumentResolver;
import org.springframework.data.web.PageableHandlerMethodArgumentResolver;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.servlet.mvc.method.annotation.RequestMappingHandlerAdapter;

import java.util.List;

@Configuration
@EnableMongoRepositories
public class RequestMappingHandlerAdapterCustomizer implements BeanPostProcessor {
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        if (bean instanceof RequestMappingHandlerAdapter) {
            RequestMappingHandlerAdapter adapter = (RequestMappingHandlerAdapter)bean;
            List<HandlerMethodArgumentResolver> customArgumentResolvers = adapter.getCustomArgumentResolvers();
            if(customArgumentResolvers != null) {
                for(HandlerMethodArgumentResolver customArgumentResolver : customArgumentResolvers) {
                    if(customArgumentResolver instanceof HateoasPageableHandlerMethodArgumentResolver) {
                        HateoasPageableHandlerMethodArgumentResolver hateoasPageableHandlerMethodArgumentResolver = (HateoasPageableHandlerMethodArgumentResolver)customArgumentResolver;
                        hateoasPageableHandlerMethodArgumentResolver.setOneIndexedParameters(true);
                    }
                    if(customArgumentResolver instanceof PageableHandlerMethodArgumentResolver) {
                        PageableHandlerMethodArgumentResolver pageableHandlerMethodArgumentResolver = (PageableHandlerMethodArgumentResolver)customArgumentResolver;
                        pageableHandlerMethodArgumentResolver.setOneIndexedParameters(true);
                    }
                }
            }
        }
        return bean;
    }
    public Object postProcessBeforeInitialization(Object bean, String beanName)
            throws BeansException {
        return bean;
    }
}
